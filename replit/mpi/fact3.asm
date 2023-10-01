;Factorial from 0 to 20(decimal) using repeated bcd addition

;convert bcd to hex and then perform bcd addition so that the output
;will be in bcd, so there wont be any need to do hex to bcd 

assume cs:code,ds:data
data segment
	num db 19H		;input bcd number
	prod1 db 00H	;output prod1prod2...prod10
	prod2 db 00H	;20! has 19 digits~20
	prod3 db 00H	;so 10 mem can store 20 digits with each storing two
	prod4 db 00H
	prod5 db 00H
	prod6 db 00H
	prod7 db 00H
	prod8 db 00H
	prod9 db 00H
	prod10 db 01H
	
	temp1 db 00H	;temporary mem variables
	temp2 db 00H	;as mov cant take 2 mem as arg
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
	
	mov ah,al		;bcd to hex start
	and ah,0Fh
	mov bl,ah
	and al,0F0h
	mov cl,04
	ror al,cl
	mov bh,0Ah
	mul bh
	add al,bl
	mov ah,al		;bcd to hex end
	
	xor cx,cx		;clearing cx
	
	jmp cond		;while loop construct -> condition first then loop context
	loop1:
		cmp cl,02	;if the loop counter/num is less than 2(i.e., 0 or 1) then
		jb endif1	;no need to perform anything
		
		;eg:
		;1*2=1+1=2
		;(1*2)*3=2+2+2=6
		;((1*2)*3)*4=6+6+6+6=24
		
		;here temp1 will be having the values 1,2,6,24... wrt to the eg
		;ch will be having the values 2,3,4.. -> no of times to add
		
		mov ch,cl
		dec ch	; we have to add ch-1 times cuz already 1 time is in the reg 
		
		mov al,prod1	;basically copying prod1 to temp1
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
		
		add1:				;repeated bcd addition
			mov al,temp10	
			add al,prod10
			daa			;decimal adjust after addition for bcd
			mov prod10,al
			
			mov al,temp9
			adc al,prod9	;adding with prev carry
			daa
			mov prod9,al
			
			mov al,temp8
			adc al,prod8
			daa
			mov prod8,al
			
			mov al,temp7
			adc al,prod7
			daa
			mov prod7,al

			mov al,temp6
			adc al,prod6
			daa
			mov prod6,al
			
			mov al,temp5
			adc al,prod5
			daa
			mov prod5,al

			mov al,temp4
			adc al,prod4
			daa
			mov prod4,al
			
			mov al,temp3
			adc al,prod3
			daa
			mov prod3,al

			mov al,temp2
			adc al,prod2
			daa
			mov prod2,al
			
			mov al,temp1
			adc al,prod1
			daa
			mov prod1,al
			
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