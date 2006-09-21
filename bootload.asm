[org 0x700]
[bits 16]

	cli
	mov ax,0
	mov ds,ax
	mov es,ax
	mov ss,ax
	mov sp,0x700
	
	mov si,msg_gotoprot
	call print
	
	mov ah,1
	mov ch,0x20
	int 0x10

	mov al,00010001b
	out 0x20,al
	mov al,0x20
	out 0x21,al
	mov al,00000100b
	out 0x21,al
	mov al,00000001b
	out 0x21,al

	cli 
	
	lgdt [gd_reg]

	in al,0x92
	or al,2
	out 0x92,al
	
	mov eax,cr0
	or eax,1

	mov cr0,eax

	jmp 0x8:_protected
print:
	pusha
_loop:
        lodsb
	test al,al
	jz _quit
	mov ah,0x0e
	int 0x10
	jmp short _loop
_quit:
	popa
	ret

[bits 32]
_protected:
	mov eax,0x10
	mov ds,eax
	mov es,eax
	nop
	mov fs,eax
	mov gs,eax
	mov ss,eax

	mov esi, kernel
	mov edi, 0x200000
	mov ecx, 0x4000
	rep movsd

;	mov edi,0xb8001
;	mov esi,[msg_test+1]
;	mov ecx,1
;	rep movsb	

	jmp 0x200000

	hlt     
	jmp short $

gdt:
	dw 0,0,0,0

	dw 0x0ffff
	db 0x00
	db 0x00
	db 0x00
	db 10011010b
	db 0xcf
	db 0x00

	dw 0x0ffff
	db 0x00
	db 0x00
	db 0x00
	db 10010010b
	db 0xcf
	db 0x00

gd_reg:
	dw 8192
	dd gdt

msg_gotoprot:  db "Goto protected mode",10,13,0
msg_test:	db 't',7,'e',7,'S',7,'T',7
kernel:
	incbin 'core'

[SECTION .bss]

_dir_entry: 
	resb 4096
_krn_table:
	resb 4096
	resb 4096
	resb 4096
_temp:	
	resd 4
