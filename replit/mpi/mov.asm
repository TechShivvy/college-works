assume cs:code,ds:data
data segment
	org 00
	len equ 05h
	org 10h
	str db 0aah,0bbh,0cdh,0deh,0efh
	org 20h
	cpy db 05 dup(?)
data ends

code segment
	org 0100h
start:
	mov ax,data
	mov ds,ax
	
	mov cx,len
	mov si,offset str
	mov di,offset cpy
	cld
	push ds
	pop es
	rep movsb
	mov ah,4ch
	int 21h
code ends
end start