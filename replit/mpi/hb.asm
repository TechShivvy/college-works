assume cs:code,ds:data
data segment
	num db 02Dh
	res db ?
data ends
code segment
	org 0100h
start:
	mov ax,data
	mov ds,ax

	xor cx,cx
	mov cl,num
	xor al,al
l1:	add al,01h
	daa
	loop l1
	;dec bl
	;jnz l1
	mov res,al
	
	mov ah,4ch
	int 21h
code ends
end start
