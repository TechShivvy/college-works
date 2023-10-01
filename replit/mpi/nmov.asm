assume cs:code,ds:data
data segment
	org 00h	
	len equ 05h
	org 10h
	str db 0aah,0bbh,0bch,0cdh,0deh
	org 20h
	str2 db 05 dup(?)
	org 30h
	where dw 00
data ends

code segment
	org 0100h
start:
	mov ax,data
	mov ds,ax
	
	mov cx,len
	mov si,offset str
	mov di,offset str2
l1:	mov al,[si]
	mov [di],al
	inc si
	inc di
	loop l1
	push ds
	pop es
	mov ah,4ch
	int 21h
code ends
end start
