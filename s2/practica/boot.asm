section .boot
bits 16
global boot
boot:
    mov [MAIN_DISK], dl
	xor ax, ax
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov si, ax
	mov di, ax
	mov bx, ax
	mov cx, ax
	mov dx, ax

    mov bp, 0x1000
    mov sp, bp
    
    mov dh, 0x01
    mov dl, [MAIN_DISK]
    mov bx, copy_target
    call load_kernel
    jmp enter_protected_mode

    jmp $
enter_protected_mode:
    call a20_stuff
    cli
    lgdt [gdt_pointer]
    mov eax, cr0 
    or al, 1
    mov cr0, eax
    jmp KERNEL_CODE_SEG:protected_main

a20_stuff:
    push ax
    mov ax, 0x2403
    int 0x15
    jb a20_ns
    cmp ah, 0
    jnz a20_ns
    mov ax, 0x2402
    int 0x15
    jb a20_failed
    cmp ah, 0
    jnz a20_failed
    cmp al,1
    jz a20_activated
    mov ax,0x2401
    int 0x15
    jb a20_failed
    cmp ah, 0
    jnz a20_failed

a20_activated:
    mov bx, A20_ON
    call print_string
    pop ax
    ret
a20_ns:
    mov bx, A20_NS
    call print_string
    jmp $
a20_failed:
    mov bx, A20_FAILED
    call print_string
    jmp $

print_string:
    pusha
print_loop:
    mov al, [bx]
    cmp al, 0
    je print_done
    mov ah, 0x0e
    int 0x10
    add bx, 1
    jmp print_loop
print_done:
    popa
    ret

print_char:
    push ax
    mov ah, 0x0e
    int 0x10
    pop ax
    ret

%include "hex.asm"

MAIN_DISK: dw 0

load_kernel:
    pusha
    push dx
    mov dl, [MAIN_DISK]
    mov ah, 0x02
    mov al, dh
    mov cl, 0x02
    mov ch, 0x00
    mov dh, 0x00
    int 0x13

    jc kernel_load_error

    pop dx
    cmp al, dh
    jne kernel_sectors_error
    mov bx, DISK_READ_OK
    call print_string
    popa
    ret
kernel_load_error:
    mov bx, DISK_READ_ERROR
    call print_string
    mov dh, ah ; ah = error code, dl = disk drive that dropped the error
    call print_hex ; check out the code at http://stanislavs.org/helppc/int_13-1.html
    jmp $
kernel_sectors_error:
    mov bx, DISK_SECTORS_ERROR
    call print_string
    jmp $

gdt_start:
    dd 0x0
    dd 0x0
gdt_kernel_code:
    dw 0xffff ; limit(0-15)
    dw 0x0  ; base(0-15)
    db 0x0  ; base(16-23)
    db 0x9a ; access byte
    db 0xcf ; 4 bits flags + 4 bits limit(16-19)
    db 0x0  ; base(24-31)
gdt_kernel_data:
    dw 0xffff
    dw 0x0
    db 0x0
    db 0x92
    db 0xcf
    db 0x0
gdt_user_code:
    dw 0xffff
    dw 0x0
    db 0x0
    db 0xfa
    db 0xcf
    db 0x0
gdt_user_data:
    dw 0xffff
    dw 0x0
    db 0x0
    db 0xf2
    db 0xcf
    db 0x0
tss:
    dd 0x0 ; modify me in the future https://wiki.osdev.org/GDT_Tutorial
    dd 0x0
gdt_end:
gdt_pointer:
    dw gdt_end - gdt_start
    dd gdt_start

KERNEL_CODE_SEG equ gdt_kernel_code - gdt_start
DISK_READ_OK: db "Disk read OK", 0x0a, 0x0d, 0
DISK_READ_ERROR: db "Disk read error", 0x0a, 0x0d, 0
DISK_SECTORS_ERROR: db "Disk sectors error", 0x0a, 0x0d, 0
A20_ON: db "A20 gate on", 0x0a, 0x0d, 0
A20_NS: db "A20 gate not supported", 0x0a, 0x0d, 0
A20_FAILED: db "A20 gate failed", 0x0a, 0x0d, 0
times 510-($-$$) db 0
dw 0xaa55

copy_target:
[bits 32]
protected_main:
	mov esp,0x100000
    mov ebp, esp
    extern main
    call main
    jmp $

print_vga:
    push eax
    mov ah, 0x0f
    mov [0xb8000], ax
    pop eax
    ret