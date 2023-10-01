assume cs:code,ds:data
data segment
	arr db 07h,0aah,0bch,01h,02h,07h
	count equ 06h
data ends
code segment
	org 0100h
start:
	mov ax,data
	mov ds,ax

	mov ch,count
l1:	mov cl,count
	mov si,offset arr
l2:	mov ax,[si]
	cmp ah,al
	jnc here
	xchg ah,al
	mov [si],ax
here:	inc si
	dec cl
	jnz l2
	dec ch
	jnz l1
			
	mov ah,4ch
	int 21h
code ends
end start

