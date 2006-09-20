[bits 16]
[org 0]

%define READ_CYL 10
%define ERRORS_MAX 5

entry:
	mov ax,cs
	mov ds,ax
	mov es,ax
	mov ss,ax
	mov sp,0x7c00

	sti
	mov ax,0x7c0
	mov ds,ax
	mov ax,0x9000
	mov es,ax

	xor si,si
	xor di,di

	mov cx,128
	rep movsd

	jmp 0x9000:start
start: 	
	mov ax,cs
	mov ds,ax
	mov ss,ax

	mov di,1
	mov ax,0x290
	xor bx,bx

copy:
	mov cx,0x50
	mov es,cx

	push di

	shr di,1
	setc dh
	mov cx,di
	xchg ch,cl
	
	pop di

	cmp di,READ_CYL
	je quit

	call read_cylinder

	pusha
	push ds
	mov cx,0x50
	mov ds,cx
	mov es,ax
	xor di,di
	xor si,si
	mov cx,0x2400
	rep movsb

	pop ds
	popa

	inc di
	add ax,0x240
	jmp short copy
quit:
     	mov ax,0x50
	mov es,ax
	mov bx,0
	mov ch,0
	mov dh,0
	call read_cylinder

	jmp 0x0000:0x0700

read_cylinder:
	
	mov [n_error],byte 0
	pusha

_start:	

	mov ah,0x02
	mov al,18
	mov cl,1

	int 0x13
	jc error
	popa
	ret

n_error: db 0
error:	
	inc byte [n_error]
	mov si,msg_err
	call print
	call printhex
	mov si,msg_n
	call print

	cmp byte [n_error],ERRORS_MAX
	jl _start
	
	mov si,msg_fatal
	call print
	hlt
	jmp short $

hex_table: db "0123456789abcdef"
	
printhex:
	pusha

	xor bx,bx
	mov bl,ah
	and bl,11110000b
	shl bl,4
	mov al,[hex_table+bx]
	call putc
	
	popa 
	ret

putc:
	pusha
	mov ah,0x0e
	int 0x10
	popa
	ret

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

msg_n:	db 0x0a,0x0d,0
msg_err:
	db "Error of reading...",0
msg_fatal:
	db "Too much errors!!! System is failed.",0
times 510-($-$$) db 0
db 0xaa,0x55
	incbin 'load2'
	
 

	


	
	