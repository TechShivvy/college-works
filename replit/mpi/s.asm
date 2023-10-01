assume cs:code,ds:data

data segment
	message db "hello hi shiv$"
data ends

code segment
	org 0100h
start:
	mov ax,data
	mov ds,ax
	mov ah,9
	mov dx,offset message
	int 21h
	mov ah,4ch
	int 21h
	code ends
end start
