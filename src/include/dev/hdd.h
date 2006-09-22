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

#endif /*HDD_H_*/
