section .text
global _start
_start:
    push 1
    pop rdi
    jmp truco
vuelta:
    pop rsi
    push 9
    pop rdx
    inc rdx
    xor rax, rax
    inc rax
    syscall
    push 60
    pop rax 
    xor rdi, rdi
    syscall
truco:
    call vuelta
db "Hola", 0