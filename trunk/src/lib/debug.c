void dump(void* mem,int size){
	int* memory = (int*)mem;
	unsigned int count = 0;
	printf("\nDump:");
	while(count<size){
		if(count%(sizeof(int)*4)==0) printf("\nAddr 0x%x: ",mem+count);
		printf("0x%x ",*(int*)(mem+count));
		count+=sizeof(int);
	}
	printf("\nEnd of dump\n");
};

void info_regs(){
	unsigned int eax;
	unsigned int ebx;
	unsigned int ecx;
	unsigned int edx;

	unsigned int esi;
	unsigned int edi;

	unsigned int cs;
	unsigned int ds;
	unsigned int es;
	unsigned int ss;

	unsigned int sp;
	

	asm("":"=a"(eax):);
	asm("":"=b"(ebx):);
	asm("":"=c"(ecx):);
	asm("":"=d"(edx):);

	asm("":"=D"(edi):);
	asm("":"=S"(esi):);

	printf("\n");
	printf("eax: 0x%x\n",eax);
	printf("ebx: 0x%x\n",ebx);
	printf("ecx: 0x%x\n",ecx);
	printf("edx: 0x%x\n",edx);

	//asm("movw %ax, %cs");
	//asm("":"=a"(cs):);
	//asm("movl %eax, %ds");
	//asm("":"=a"(ds):);
	//asm("movl %eax, %es");
	//asm("":"=a"(es):);
	//asm("movl %eax, %ss");
	//asm("":"=a"(ss):);

	asm("movl %eax, %esp");
	asm("":"=a"(sp):);

	//printf("cs: 0x%x\n",cs);
	//printf("ds: 0x%x\n",ds);
	//printf("es: 0x%x\n",es);
	//printf("ss: 0x%x\n",ss);

	printf("edi: 0x%x\n",edi);
	printf("esi: 0x%x\n",esi);
	printf("sp: 0x%x\n",sp);
};

