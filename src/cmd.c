void cmd_out(){
	char s_port[10],s_value[10];
	printf("\nPort>");
	gets(s_port,sizeof(s_port));
	printf("\nValue>");
	gets(s_value,sizeof(s_value));
	outportb(h_short(s_port,sizeof(s_port)),h_char(s_value,sizeof(s_value)));
};

void cmd_in(){
	char s_port[10];
	printf("\nPort>");
	gets(s_port,sizeof(s_port));
	unsigned char value=inportb(h_short(s_port,sizeof(s_port)));
	int val=value;
	printf("\nValue> %x",val);
};

void cmd_dump(){
	char s_size[10],s_addr[20];
	printf("\nDump memory\nInput addr:");
	gets(s_addr,sizeof(s_addr));
	printf("\nSize:");
	gets(s_size,sizeof(s_size));
	printf("\n");
	dump(h_int(s_addr,sizeof(s_addr)),h_int(s_size,sizeof(s_size)));
};	

void empty(char* str,int size){
	int i;
	for(i=0;i<size;i++){
		str[i]=0;
	};
	return;
};

void help(){
	printf("\nOut - outport\nIn - inport\nDump - dump of memory\n");
	return;
};

void console(){
	char cmd[40];
	while(1){
		printf("\n>");
		gets(cmd,sizeof(cmd));
		if(cmp(cmd,"out")){cmd_out();}
 		else if(cmp(cmd,"in")){cmd_in();}
		else if(cmp(cmd,"dump")){cmd_dump();}
		else help();
		empty(cmd,sizeof(cmd));
	}
};
