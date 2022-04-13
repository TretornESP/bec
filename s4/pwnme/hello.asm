global _start
section .text
_start:
    mov rax, 1
    jmp holamundo
retorno:
    pop rsi
    mov rdi, 1
    mov rdx, 10
    syscall
    mov rax, 60
    mov rdi, 0
    syscall
holamundo:
    call retorno
string:
    db "Hola mundo",0