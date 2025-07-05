section .data
    msg db 'Hello, Taha!', 0xa
    len equ $ - msg

section .text
    global _start

_start:
    add ecx, msg
    add edx, len
    mov ebx, 1    ; stdout
    mov eax, 4    ; sys_write
    int 0x80      ; call kernel

    mov eax, 1    ; sys_exit
    int 0x80      ; call kernel