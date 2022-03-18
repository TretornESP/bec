[BITS 16]
[ORG 0x7c00]

mov [DISK], dl

xor ax, ax
mov ds, ax
mov ss, ax
mov es, ax
mov si, ax
mov di, ax
mov bx, ax
mov cx, ax
mov dx, ax

mov sp, 0x1000
mov bp, sp

mov dh, 0x01
mov cl, 0x02
mov dl, [DISK]
mov bx, 0x8000
call disk_load
call print_string

;registramos la interrupcion
mov word [0x24], keypress_detected
mov word [0x26], 0

jmp $

keypress_detected:
    mov al, 'K'
    mov ah, 0x0e
    int 0x10
    jmp $

;Esta funcion imprime la cadena
;Cuya dir de mem esté en bx
print_string:
    push ax
    mov al, [bx]
    cmp al, 0
    je exit_print

    call print_char

    inc bx
    jmp print_string
    
exit_print:
    pop ax
    ret

;Esta funcion imprime el caracter
;que se envie por al, en pantalla
print_char:
    push ax
    mov ah, 0x0e
    int 0x10
    pop ax
    ret

DISK: db 0
STRING: db 'Hola buenas que tal', 0

%include "disk.asm"

times 510 - ($ - $$) db 0
dw 0xAA55
db 'Estoy en el segundo sector', 0
