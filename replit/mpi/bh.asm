assume cs:code,ds:data
data segment
	num db 17h
	res db ?
data ends
code segment
	org 0100h
start:
	mov ax,data
	mov ds,ax
	
	mov al,num
	mov bl,al
	and bl,0fh
	and al,0f0h
	mov cl,04h
	ror al,cl
	mov dl,0Ah
	mul dl
	add al,bl
	mov res,al
	mov ah,4ch
	int 21h
code ends
end start