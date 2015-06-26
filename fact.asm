section .data
	rmsg db "aaaa", 10, 0
	emsg db "bbbb",10,0

section .text
	global main
	extern printf
	extern atoi
	extern myFact

main:	enter 0,0
	mov ebx,dword[ebp+8]
	
	cmp ebx,2
	je lp1

	push emsg
	call printf
	add esp,4
	jmp ex

lp1:	mov ebx,dword[ebp+12]
	push dword[ebx+4]
	call atoi
	add esp,4
	xor ebx,ebx
	mov ebx,eax

	push ebx
	call myFact
	add esp,4
	mov ecx,eax

	push ecx
	push ebx
	push rmsg
	call printf
	add esp,12

ex:	leave
	ret