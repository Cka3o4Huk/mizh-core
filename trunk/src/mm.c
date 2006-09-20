#include "include/addr.h"
#include "include/common.h"

/** Comment by Zhilin Mike 2-dec-2005 
*   Reason:	Unknown old code
*

char* mem=MAP_MEM;

char* inc_mem(int size){
	char* addr;
	int offset=find_empty(size);	
	int i;
	for(i=0;i<size;i++){
		mem[offset+i]=0xff;
	};
	addr=offset<<15;
	return addr;
};

void dec_mem(char* addr,int size){
	int offset=addr>>15;
	int i;
	for(i=0;i<size;i++){
		mem[offset+i]=0x00;
	};
};
*/

#define DIR_INDEX(t) ((t>>22)&0x3ff)
#define TBL_INDEX(t) ((t>>12)&0x3ff)

/** 	
 * Kernel Address Space 0xC0000000-0xFFFFFFFF (3Gb - 4Gb)
 **/
#define KRN_VIRT_ADDR	0x00000000
#define KRN_PHYS_ADDR	0x00200000
#define KRN_CODE_SIZE	0x00200000
#define KRN_DATA_SIZE	0x00200000	 

#define PRIV_USER	0x04
#define PRIV_WRBL	0x02
#define PRIV_PRST	0x01

typedef unsigned short  ushort;
typedef unsigned int 	uint;	
typedef unsigned long 	u32;

int init_memory(u32 *dir,u32 krn_table);
static int add_table(u32 addr_table,u32 addr_virt,u32 *dir);
static int map_page(u32 *dir,unsigned int priv,u32 virt,u32 phys);
static int init_table(u32 addr_virt,u32 size,u32 addr_phys,u32 *dir,unsigned int priv);

int init_memory(u32 *dir,u32 krn_table){
	if(add_table(krn_table,KRN_VIRT_ADDR,dir)!=0) return -1;
//	if(add_table(krn_table+4096,0,dir_entry)!=0) return;
	if(init_table(KRN_DATA_SIZE,KRN_CODE_SIZE,KRN_PHYS_ADDR,dir,PRIV_PRST|PRIV_USER)!=0) return -2;
	if(init_table(0,KRN_DATA_SIZE,0,dir,PRIV_PRST|PRIV_WRBL|PRIV_USER)!=0) return -3;
//	if(init_table(0,0x400000,0,dir_entry,PRIV_PRST|PRIV_WRBL)!=0) return;
	return 0;
}
	
static int add_table(u32 addr_table,u32 addr_virt,u32 *dir){

	unsigned int index_dir;	
        index_dir = DIR_INDEX(addr_virt);	

	if(dir[index_dir]!=0) return -1;
	
	dir[index_dir] = (addr_table & 0xFFFFF000L)|(PRIV_USER|PRIV_WRBL|PRIV_PRST);
	
	return 0;	
}

static int map_page(u32 *dir,unsigned int priv,u32 virt,u32 phys){
	
	unsigned int index_dir, index_tab;
	unsigned long *tab;

	index_dir = DIR_INDEX(virt);
	if(dir[index_dir] == 0) return -1;

	tab = (unsigned long *)(dir[index_dir] & 0xFFFFF000L);

	index_tab = TBL_INDEX(virt);
	priv &= 0xFFF;
	tab[index_tab] = (phys & 0xFFFFF000L) | priv;

	return 0;	
}

static int init_table(u32 addr_virt,u32 size,u32 addr_phys,u32 *dir,unsigned int priv){
	
	u32 virt;
	u32 phys;

	phys = addr_phys;
	
	for(virt=addr_virt; virt<addr_virt+size; virt+= 4096){
		if(map_page(dir,priv,virt,phys)<0) return -1;
		phys+=4096;
	}
	return 0;
}

void clear_memory(unsigned char *start,unsigned long size){
	
	u32 index;
	
	if(size<=0) return;
	for(index=0;index<size;index++){
		start[index]=0;
	}
}

void core_alloc(w_dword size){
    
}

