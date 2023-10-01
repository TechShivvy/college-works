
;Factorial

assume cs:code,ds:data
data segment
	num db 19H
	prod1 db 01H
	prod2 db 00H
	prod3 db 00H
	prod4 db 00H
	prod5 db 00H
	prod6 db 00H
	prod7 db 00H
	prod8 db 00H
	prod9 db 00H
	prod10 db 00H
	temp1 db 00H
	temp2 db 00H
	temp3 db 00H
	temp4 db 00H
	temp5 db 00H
	temp6 db 00H
	temp7 db 00H
	temp8 db 00H
	temp9 db 00H
	temp10 db 00H

data ends
code segment
	org 0100h
start:
	mov ax,data
	mov ds,ax
	
	mov al,num
	
	
	
	xor cx,cx
	mov num,ah	
	mov ah,4ch
	int 21h
	code ends
end start
