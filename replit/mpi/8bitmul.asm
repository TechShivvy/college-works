assume cs:code,ds:data
data segment
	opr1 db 05h
	opr2 db 03h
	result dw ?
data ends
code segment
	org 0100h
start:mov ax,data
	mov ds,ax
	mov al,opr1
	mov bl,opr2
	mul bl
	mov result,ax
	mov ah,4ch
	int 21h
code ends
end start