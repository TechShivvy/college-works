assume cs:code,ds:data
data segment
	org 00h	
	len equ 05h
	org 10h
	str db 0aah,0bbh,0bch,0cdh,0deh
	org 20h
	str2 db 0aah,0bbh,0bch,0cdh,0d1h
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
	cld
	push ds
	pop es
	
	repe cmpsb
	jz l1
	inc cx
l1:	mov where,cx
	
	mov ah,4ch
	int 21h
code ends
end start