
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
	
	mov ah,al
	and ah,0Fh
	mov bl,ah
	and al,0F0h
	mov cl,04
	ror al,cl
	mov bh,0Ah
	mul bh
	add al,bl
	mov ah,al
	
	xor cx,cx
	
	jmp cond
	loop1:
		cmp cl,02
		jb endif1
		mov ch,cl
		dec ch
		
		mov al,prod1
		mov temp1,al
		mov al,prod2
		mov temp2,al
		mov al,prod3
		mov temp3,al
		mov al,prod4
		mov temp4,al
		mov al,prod5
		mov temp5,al
		mov al,prod6
		mov temp6,al
		mov al,prod7
		mov temp7,al
		mov al,prod8
		mov temp8,al
		mov al,prod9
		mov temp9,al
		mov al,prod10
		mov temp10,al
		
		add1:
			mov al,temp1
			add al,prod1
			daa
			mov prod1,al
			
			mov al,temp2
			adc al,prod2
			daa
			mov prod2,al
			
			mov al,temp3
			adc al,prod3
			daa
			mov prod3,al
			
			mov al,temp4
			adc al,prod4
			daa
			mov prod4,al

			mov al,temp5
			adc al,prod5
			daa
			mov prod5,al
			
			mov al,temp6
			adc al,prod6
			daa
			mov prod6,al

			mov al,temp7
			adc al,prod7
			daa
			mov prod7,al
			
			mov al,temp8
			adc al,prod8
			daa
			mov prod8,al

			mov al,temp9
			adc al,prod9
			daa
			mov prod9,al
			
			mov al,temp10
			adc al,prod10
			daa
			mov prod10,al
			
			clc
			dec ch
			cmp ch,0
			jne add1
			
		endif1:
			inc cl
			
	cond:
		cmp cl,ah
		jbe loop1
	mov ah,4ch
	int 21h
	code ends
end start