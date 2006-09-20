#include "include/idt.h"

char str[80];

void k_init_ata(){
    if(ata_detect(0x1f0,0x00)==0){
        if(ata_info(0x1f0,0x00)!=0) 
            printf("HDD: Timeout or another error occupied\n");          
            call_stack_out();
    }else{
        printf("HDD isn't detected\n");
    }
}

void k_main(){
	int x=0;
	init_ints();
	printf("Welcome to MiZh Core v.0.0.1a(planning status)\n");
    
    k_init_ata();
    
    //k_init_fs();
    
//    test_hdd(0x1f0,0x10);
//    test_hdd(0x170,0x00);
//    test_hdd(0x170,0x10);

	printf("Test: division by zero... \n");	
	x=5/x;
	//info_regs();
	//console();    
	//asm("int $80");
	//load_daemon();
	while(1);
}
