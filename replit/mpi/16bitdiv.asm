assume cs:code,ds:data
data segment
	opr1 dw 0017h
	opr2 db 03h
	q db ?
	r db 00 
data ends
code segment 
	org 0100h
start:	mov ax,data
		mov ds,ax
		mov ax, opr1
		mov bl,opr2
		div bl
		mov q,al
		mov r,ah
		mov ah,4ch
		int 21h
code ends
end start