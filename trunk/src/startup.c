#include "addr.h"

void _start(){

	/*
	* 0x1000 - 0x1FFF - Dir Entry for paging
	* 0x2000 - 0x9FFF - Kernel entries (8) for first 4x8 Megs
	*/         
	unsigned long *dir;
	int status;
	int i;

	//for(i=0x0;i<80*25;i++)	*(unsigned short*)(0xb8000+i*2)=0x0720;
	
	init_tty();

	clear();

	printf("Memory init...");

	dir = (unsigned long*)PAGE_DIR;

	clear_memory(dir,PAGE_DIR_SIZE+8*PAGE_ENT_SIZE);
	status = init_memory(dir,(unsigned long)(dir+PAGE_DIR_SIZE));
	if(status!=0){
		if(status==-1) printf("Error 1");
		if(status==-2) printf("Error 2");
		if(status==-3) printf("Error 3");
		while(1);
	}

	for(i=0;i<10000000;i++){};

	asm("	movl %0, %%cr3;\
		movl %%cr0, %%eax;\
		or  $0x80000000, %%eax;\
		movl %%eax,%%cr0": :"r"(dir));	

	printf("Ok\n");	

	while(1){};

	k_main();
}
