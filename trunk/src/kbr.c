#include "include/scan.h"
#include "include/idt.h"
#include "include/kbr.h"

#define IRQ_HANDLER(func) void func(void);\
 asm("\n_"#func":cli\n pusha\n call __" #func "\n movb $0x20, %al \n outb %al, $0x20\n popa\n sti\n iret\n");\
 void __##func(void)

void dummy_intr();
asm("\n_dummy_intr:\n movb $0x20,%al\n	outb %al,$0x20 \n iretl");

char shift=0;

char *buf=NULL;
int count=0;
int finish=0;

void gets(char* s,int size){
	disable_intr();
	buf=s;
	count=size;
	enable_intr();
	while(!finish){};
	disable_intr();
	finish=0;
	buf=NULL;
	count=0;
	enable_intr();
}

IRQ_HANDLER(irq_keyboard){
	unsigned char scancode,ascii,creg;

	scancode=inportb(0x60);

	switch(scancode){
		case 0x2a:
		case 0x36:
			shift=1;
			break;
		case 0x2a+0x80:
		case 0x36+0x80:
			shift=0;
			break;
		default:

			if(scancode>=0x80){
			}else{
				if(shift){
					ascii=scancodes_shifted[scancode];
				}else{
					ascii=scancodes[scancode];
				}
				if(!ascii)break;
				if(buf&&(count>0)){
					*buf=ascii;
					buf++;
					count--;
				}
				if((count==0)||(ascii=='\n')){
					finish=1;
					*buf='\0';
				}
			};
			break;
	};

	creg = inportb(0x61);
	creg|=1;
	outportb(0x61,creg);
}

void* get_keyboard_handler(){
	return &irq_keyboard;
}
