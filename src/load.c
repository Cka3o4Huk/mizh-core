void load_daemon(){

	int pointer;
	int key;
	struct mem_entry* mem_pointer;

	pointer = fs_entry("daemon",O_RDONLY);
	if(pointer < 0){
		perror("Error of fs_entry\n");
		sys_halt();
	}

	key = key(FS,"daemon");
	if(key<0){
		perror("Error of filesystem key\n");
		sys_halt();
	}
	
	mem_pointer = mem_entry(key,O_CREAT);
	if(mem_pointer==NULL)
	        perror("Error of memory entry\n");
		sys_halt();
	}
		
	if(load(mem_pointer,pointer)<0){
		perror("Error of loading memory\n");
		sys_halt();
	}
	
	if((od=sys_object(key,mem_pointer,"daemon"))<0){
		perror("Error of creating object memo\n");
		sys_halt();
	}
	
	if(add_switch(od)<0){
		perror("Error of creating switch memo\n");
		sys_halt();
	}

	switch();

}

