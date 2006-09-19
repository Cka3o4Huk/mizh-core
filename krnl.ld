SECTIONS
{
/* kernel code */
/*    .text 0x200000 :*/
    .text 0x00200000 :
    {	*(.text)
	. = ALIGN(4096);
	_etext = .;
    }
/* kernel data */
    .data :
    {	*(.data)
	. = ALIGN(4096);
	_edata = .;
    }
/* kernel BSS */
    .bss :
    {	*(.bss)
	*(COMMON)
	_end = .;
    }
}
