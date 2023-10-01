assume cs:code,ds:data
data segment
	opr1 db 05h
	opr2 db 07h
	result db 00h
	carry db 00h
data ends
code segment
	org 0100h
start:
	mov ax,data
	mov ds,ax
	mov ah,opr1
	mov bh,opr2
	sub ah,bh
	jnc here
	inc ch
	neg ah
here:
	mov result,ah
	mov carry,ch
	mov ah,4ch
	int 21h
code ends
end start
