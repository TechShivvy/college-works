assume cs:code,ds:data
data segment
	hr db 01 dup(?)
	min db 01 dup(?)
	sec db 02 dup(?)
data ends
code segment
	org 0100h
start:
	mov ax,data
	mov ds,ax
	
	mov ah,2ch
	int 21h
	
	mov si,offset hr
	mov [si],CH
	
	mov si,offset min
	mov [si],cl
	
	mov si,offset sec
	mov [si],dh
	
	mov ah,4ch
	int 21h
	
code ends
end start