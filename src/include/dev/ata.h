#ifndef HDD_H_
#define HDD_H_

#include "../../include/common.h"
#include "../../include/idt.h"

/*
 * Errors
 */
 
#define ERROR_ATA 0xFFFF0000 

/*
 * Status Register for ATA (begin block)
 */

//Busy Status
#define STATUS_BUSY 0x80 

//Drive Ready
#define STATUS_DRDY 0x40

//Drive Write Fault
#define STATUS_DWF  0x20

//Drive Seek Complete
#define STATUS_DSC  0x10

//Data Request
#define STATUS_DRQ  0x08

//Correction bit
#define STATUS_CORR 0x04

//Index
#define STATUS_INDX 0x02

//Error
#define STATUS_ERR  0x01

/*
 * End Block for Status Register ATA
 */
#define MODE_NO     0x00
#define MODE_YES    0x01

#define ATA_INFO    0xEC
#define ATA_READ    0x20

void*   hdd_buf;
#define ATA_BUFFER 	0xAE00
#define ATA_BUFFER_SIZE 0x200

#define ATA_CHANNEL_0 		0x1F0
#define ATA_CHANNEL_1		0x170
#define ATA_PRIMARY_DEVICE 	0x00
#define ATA_SECOND_DEVICE 	0x10

#define ATA_TOTAL_TIME	500000

/*
 * Command types
 */

#define ATA_CMD_ND
#define ATA_CMD_PI
#define ATA_CMD_PO
#define ATA_CMD_DMA

typedef struct _ata_job_struct{
	w_word  port;
	w_byte	device_id;
	w_byte  command;
	w_byte	cmd_type;
	w_byte	sect_count;
	w_byte  sect_number;
	w_byte  cyl_low;
	w_byte  cyl_high;	
}ata_job_struct;


#endif /*HDD_H_*/
