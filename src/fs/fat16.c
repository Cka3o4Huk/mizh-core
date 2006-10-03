#include "addr.h"
#include "dev/hdd.h"
#include "fs/fat16.h"

void read_fat16(){
	
	/*
	 * Reading boot sector
	 */
	 
	ata_read_data(ATA_CHANNEL_0,ATA_PRIMARY_DEVICE, 0x01,0x00,0x00);
	
	/*
	 * Verify FAT16
	 */
	
	hdd_buf = ATA_BUFFER;
	
	printf("File SysID: %S \n",(hdd_buf+FAT16_FILE_SYSID_OFFSET),8);
	printf("File SysID: %S \n",(hdd_buf+FAT32_FILE_SYSID_OFFSET),8);
	printf("Sign: %x \n", *(w_word *)((void*)hdd_buf+0x1FE));
		
}
