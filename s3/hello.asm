section .text
    global _start
_start:
    jmp message
shellcode:
    xor rax, rax    ; clear register
    xor rdi, rdi
    xor rdx, rdx
    mov al, 0x1     ; system call for write
    mov dil, 0x1
    pop rsi
    mov dl, 0xF
    syscall
    mov al, 0x3c    ; system call for exit
    xor rdi, rdi
    syscall
message:
    call shellcode
    db "Hello, World!", 0ah