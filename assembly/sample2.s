section .data
    msg db 'Hello, Taha!', 0xa
    len equ $ - msg

section .text
    global _start

_start:
    mov ecx, msg
    mov edx, len
    mov ebx, 1    ; stdout
    mov eax, 4    ; sys_write
    int 0x80      ; call kernel

    mov eax, 1    ; sys_exit
    mov ebx, 0    ; exit code 
    int 0x80      ; call kernel