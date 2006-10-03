#include "idt.h"

w_dword kv;  
w_dword curr_gdt_index;

void die(){
	while(1){};
}

void _verify_type(){
	if(sizeof(w_byte)!=1){
		printf("Error: byte!=1");
		die();
	}
	if(sizeof(w_word)!=2){
	 	printf("Error: word!=2");
		die();
	}
	if(sizeof(w_dword)!=4){
	 	printf("Error: dword!=4");
		die();
	}

	return;
}

void gdt_install(unsigned int index,unsigned int addr,unsigned int limit,unsigned char type, unsigned char level){
    
    char *table = (char*)GDT_TABLE;
    unsigned char i;
    unsigned char d[8];

    d[0]=limit & 0x000000ff;
    d[1]=(limit & 0x0000ff00)>>8;
    d[2]=addr & 0x000000ff;
    d[3]=(addr & 0x0000ff00)>>8;
    d[4]=(addr & 0x00ff0000)>>16;
    d[5]=((type & 0x1f) | ((level & 0x3)<<5)) | ((type & 0x20)<<2) ;
    d[6]=((limit & 0x000f0000)>>16) | (type&0xc0); 
    d[7]=(addr & 0xff000000)>>24;

    for(i=0;i<8;i++) *(table+index*8+i)=d[i];   
}

void idt_install(unsigned char vector,void (*func)(),unsigned short selector,unsigned char type){

	char *table = (char*)IDT_TABLE;
	unsigned char i;
	unsigned char b[8];

	b[0]=(unsigned int)func & 0x000000ff;
	b[1]=((unsigned int)func & 0x0000ff00)>>8;
	b[2]=selector & 0x00ff;
	b[3]=(selector & 0xff00)>>8;
	b[4]=0;
	b[5]=type;
	b[6]=((unsigned int)func & 0x00ff0000)>>16;
	b[7]=((unsigned int)func & 0xff000000)>>24;

	for(i=0;i<8;i++) *(table+vector*8+i)=b[i];
}

t_selector tss_install(void* tss,void* page_dir,unsigned long eip,unsigned long flags){
	
	unsigned int res;

	res = (curr_gdt_index&0x7FFF)<<3 & 0xFFF8; 

	/*
	 * See Intel Development Manual for System Programming vol.3
	 */

	*(unsigned long*)((unsigned char*)tss+36)=flags;
	*(unsigned long*)((unsigned char*)tss+32)=eip;
	*(unsigned long*)((unsigned char*)tss+28)=(unsigned long)page_dir;
	
	gdt_install(curr_gdt_index,(unsigned int)tss,(unsigned int)0xFF,O_TSS|O_PRESENT,0x00);
    
	curr_gdt_index++;
	
	return res;	
}

t_selector task_install(w_dword task_id,unsigned eip,unsigned flags){    
    void* tss;
    void* page_dir;
    t_selector res;
    
    if(task_id > 79) return -1;
    
    tss = (void*)(TSS_TABLE+0xFF*task_id);
    page_dir = (void*)(PAGE_DIR);
    //((w_dword*)tss+
        
    res = tss_install(tss,page_dir,eip,flags);
    return res;    
}

void ltr(t_selector selector){
	asm ("ltr %0": :"r" (selector));
}

t_selector str(void){
	t_selector selector;

	asm ("str %0":"=r" (selector));
	return selector;
}

void gdt_init(){
	unsigned short* limit=(unsigned short*)GDT_ADDR;
	unsigned int* addr=(unsigned int*)(GDT_ADDR+2);

	*limit 	= 8192;
	*addr	= GDT_TABLE; 
    
    // Set Null Descriptor
    *(w_dword*)(GDT_TABLE)=0x0;
	*(w_dword*)(GDT_TABLE+4)=0x0;
    
	asm("lgdt 0(,%0,)"::"a"(GDT_ADDR));
}

void idt_init(){
	unsigned short* limit=(unsigned short*)IDT_ADDR;
	unsigned int* addr=(unsigned int*)(IDT_ADDR+2);

    *limit=256*8-1;
	*addr=IDT_TABLE;

	asm("lidt 0(,%0,)"::"a"(IDT_ADDR));
}

void enable_intr(){
	asm("sti");
}

void disable_intr(){
	asm("cli");
}

__inline__ void outportb(unsigned short port,unsigned char value){
	asm("outb %b0,%w1"::"a"(value),"d"(port));
}
__inline__ w_byte inportb(unsigned short port){
	w_byte value;
	asm("inb %w1,%b0":"=a"(value):"d"(port));
	return value;
}
__inline__ void outportw(w_word port,w_word value){
    asm("outw %w0,%w1"::"a"(value),"d"(port));
}
__inline__ w_word inportw(unsigned short port){
    w_word value;
    asm("inw %w1,%w0":"=a"(value):"d"(port));
    return value;
}

void init_8259a(){
	static const unsigned irq0=0x20, irq8=0x28;

	outportb(0x20,0x11);
	outportb(0xa0,0x11);

	outportb(0x21,irq0);
	outportb(0xa1,irq8);

	outportb(0x21,0x04);
	outportb(0xa1,0x02);

	outportb(0x21,0x01);
	outportb(0xa1,0x01);
//mask timer and keyboard
	outportb(0x21,0x03);
	outportb(0xa1,0x00);
}

void dummy_intr();
asm("\n_dummy_intr:\n movb $0x20,%al\n	outb %al,$0x20 \n iretl");

void sched(){
	if(kv==100){
		//printf("Kvant\n");
		kv=0;
	}
	kv++;
}

IRQ_MASTER_HANDLER(irq_timer){
	sched();
}

/*
 * Exceptions
 */
void general_protection_exception(){
    disable_intr();
    printf("\n Exception: General Protection!");
    die();
}
void tss_invalid_exception(){
    disable_intr();
    printf("\n Exception: TSS invalid!");
    die();
}
void page_fault_exception(){
    disable_intr();
    printf("\n Exception: Page Fault!");
    die();
}
void segment_not_present_exception(){
    disable_intr();
    printf("\n Exception: Segment isn't presentz!");
    die();
}
void except(){
	//Die
	disable_intr();
	printf("\n\nException!!!!");
	die();
};
void div_zero()
{
	unsigned long	eip;
	unsigned int    cs;
	//If not error code
    asm("movl 4(%%ebp),%%eax\n movl 8(%%ebp),%%bx\n":"=a"(eip),"=b"(cs));
	
	printf("Exception 0x00: Division by Zero\n");
	printf("EIP = 0x%x  CS = 0x%x",eip,cs);
	printf("\nStop machine!!!");
	die();
	asm("iret");

}
/*
 * Initialize all Tables and segments(GDT,IDT,TSS)
 */
void init_ints(){
	int i = 0;
	kv = 0;
	curr_gdt_index = 3;

	_verify_type();

    printf("Initialize GDT...");

    gdt_install(0x01,0x00,0xfffff,O_PRESENT|O_CODE_RD|O_USE32|O_GRANULAR,0x00);
    gdt_install(0x02,0x00,0xfffff,O_PRESENT|O_DATA_RDWR|O_USE32|O_GRANULAR,0x00);
    gdt_init();
    
    printf("Ok\n");    
    
    printf("Initialize IDT...");
    
	for(i=1;i<=0x20;i++){
		idt_install(i,&except	,CODE_SELECTOR,0x8e);
	};
    idt_install(0x00,&div_zero	                    ,CODE_SELECTOR,0x8e);
    idt_install(0x0A,&tss_invalid_exception         ,CODE_SELECTOR,0x8e);
    idt_install(0x0B,&segment_not_present_exception ,CODE_SELECTOR,0x8e);
    idt_install(0x0D,&general_protection_exception  ,CODE_SELECTOR,0x8e);
    idt_install(0x0E,&page_fault_exception          ,CODE_SELECTOR,0x8e);
       
	idt_install(0x20,&irq_timer	,CODE_SELECTOR,0x8e);
	idt_install(0x21,get_keyboard_handler(),CODE_SELECTOR,0x8e);
    idt_install(0x2e,get_irq_hdd()   ,CODE_SELECTOR,0x8e);
    idt_install(0x2f,get_irq_hdd2()  ,CODE_SELECTOR,0x8e);
	//idt_install(0x80,&irq_test	,CODE_SELECTOR,0x8e);

	idt_init();
	enable_intr();
    
    printf("Ok\n");
    
/*    printf("Initialize Task's Support...");
    t_selector sel_main = task_install(0x00,0x00,0x00);
    printf("Load TR...");
    ltr(sel_main);
    
    printf("Ok\n");*/
}
