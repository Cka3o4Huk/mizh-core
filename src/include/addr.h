#ifndef _ADDR_H
#define _ADDR_H

#define MAP_MEM 0x1000

/* Virtual = Physical (now for kernel)
 * Physical Memory map:
 * 0x1000 - 0x1FFF - Dir Entry for paging
 * 0x2000 - 0x9FFF - Kernel entries (8) for first 4x8 Megs
 * 0xA000 - 0xA7FF - idt space
 * 0xA800 - 0xA805 - idt reg
 * 0xA806 - 0xA80B - gdt reg
 * 0xA80C - 0xADFF - free space
 * 0xAE00 - 0xAFFF - buffer for reading data from ATA devices
 * 0xB000 - 0x10000 - first 80 tasks (task = 256 bytes) (MAPPED - Shared System Data + 0x10000)
 * 0x10000 - 0x20000 - gdt space (MAPPED - Shared System Data + 0x00000)
 * 0xB8000 - 0xC0000 - video ram
 * 0x200000 - kernel space
 */

/*
 * 0x1000 - 0x1FFF - Dir Entry for paging
 * 0x2000 - 0x9FFF - Kernel entries (8) for first 4x8 Megs
 */
#define PAGE_DIR 		0x1000
#define PAGE_DIR_SIZE 	0x1000
#define PAGE_ENT_SIZE	0x1000

/*
 * 0xA000 - 0xA7FF - idt space
 * 0xA800 - 0xA805 - idt reg
 * 0xA806 - 0xA80B - gdt reg
 * 0xA80C - 0xAFFF - empty
 */
#define IDT_ADDR 	0xA800 //6 bytes
#define IDT_TABLE 	0xA000

/*
 * 0x0B000 - 0x10000 	- first 80 tasks (task = 256 bytes) (MAPPED - Shared System Data + 0x10000)
 */
#define TSS_TABLE	0xB000

//0x10000-0x20000 	- gdt space (MAPPED - Shared System Data + 0x00000)
#define GDT_ADDR	0xA806
#define GDT_TABLE	0x10000

//0xB8000-0xC0000 	- video ram
//0x200000 			- kernel space

#define KRNL 	0x200000

//-------------------------------
//----- Virtual Addresses -------
//-------------------------------

//Shared System Data
#define SSD		0xC0000000
#define GDT 	SSD
#define TSS		SSD+0x10000

#define CORE	SSD+KRNL

#endif
