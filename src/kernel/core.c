#include "idt.h"

//char str[80];

void k_init_ata(){
	
	/*
	 * Try init first channel and first driver
	 */
	
    if(ata_detect(0x01f0,0x00)==0){
    	printf("ATA Info reading...");
        if(ata_info(0x1f0,0x00)!=0) 
            printf("HDD: Timeout or another error occupied\n");          
            //call_stack_out();
        printf("all correct\n");
    }else{
        printf("HDD isn't detected\n");
    }
}

void k_main(){
	int x=0;
	init_ints();
	printf("Welcome to MiZh Core v.0.0.1a(planning status)\n");
    
    k_init_ata();    
    
    printf("Test HDD: ata0-0\n");
    test_hdd(0x1f0,0x00);
    
    printf("Read Fat\n");
    read_fat16();
	printf("Test: division by zero... \n");	
	x=5/x;

	while(1);
}
