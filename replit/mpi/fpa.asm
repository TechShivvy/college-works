assume cs:code,ds:data
data segment
	org 00h
	x dd 20.4375
	org 10h
	y dd 20.4375
	org 20h
	res dd ?
data ends
code segment
	org 0100h
start:
	mov ax,data
	mov ds,ax
	
	finit 
	fld x
	fld y
	fadd
	fst res
	
	mov ah,4ch
	int 21h
code ends 
end start