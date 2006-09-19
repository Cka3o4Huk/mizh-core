#include "addr.h"
#include "common.h"

#define IRQ_MASTER_HANDLER(func) void func (void);\
 asm("\n_" #func ":cli\n pusha\n call __" #func "\n movb $0x20, %al \n outb %al, $0x20\n popa\n sti\n iret\n");\
 void _ ## func(void)

#define CODE_SELECTOR 	0x08

//access byte - fifth byte of descriptor

#define O_RING0 	0x00
#define O_RING1 	0x20
#define O_RING2 	0x40
#define O_RING3 	0x60

/*
 * Types of Simple Descriptors
 */

#define O_NOSYS     0x10
#define O_PRESENT   0x20

#define O_ACCESS 	0x01
#define O_DATA_RD 	0x00|O_NOSYS
#define O_DATA_RDWR 0x02|O_NOSYS
#define O_STACK 	0x06|O_NOSYS
#define O_CODE 		0x08|O_NOSYS
#define O_CODE_RD 	0x0a|O_NOSYS
#define O_GRANULAR 	0x80
#define O_USE32 	0x40

/*
 * System Types (Specifical Descriptors)
 */

/*
 * Task Descriptor
 */

#define O_BUSY      0x02
#define O_TSS       0x09

#define O_CALLGATE 	0x0c
#define O_TASKGATE 	0x05
#define O_INTERRUPT 0x0e
#define O_TRAP 		0x0f
#define O_LDT    	0x02

struct TSS32 {
   unsigned short backlink, __blh;
   unsigned long esp0;
   unsigned short ss0, __ss0h;
   unsigned long esp1;
   unsigned short ss1, __ss1h;
   unsigned long esp2;
   unsigned short ss2, __ss2h;
   unsigned long cr3, eip, eflags;
   unsigned long eax,ecx,edx,ebx,esp,ebp,esi,edi;
   unsigned short es, __esh;
   unsigned short cs, __csh;
   unsigned short ss, __ssh;
   unsigned short ds, __dsh;
   unsigned short fs, __fsh;
   unsigned short gs, __gsh;
   unsigned short ldt, __ldth;
   unsigned short trace, iomapbase;
};

typedef w_word  t_selector;
