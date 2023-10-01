assume cs:code,ds:data
data segment
	opr1 db 25h
	opr2 db 30h
	res db ?
	carry db ?	
data ends
code segment
	org 0100h
start:
	mov ax,data
	mov ds,ax

	mov al,opr1
	mov bl,opr2
	sub al,bl
	das
	mov res,al
	xor ax,ax
	adc al,al
	mov carry,al			

	mov ah,4ch
	int 21h
code ends
end start



