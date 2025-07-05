section .data
    promptMsg db 'Enter your name? '
    promptLen equ $ - promptMsg
    helloMsg db 'Hello, '
    helloLen equ $ - helloMsg

section .bss
    buffer resb 256  ; reserve 256 bytes for input

section .text
    global _start

_start:
    mov ecx, promptMsg
    mov edx, promptLen
    mov eax, 4    ; sys_write
    mov ebx, 1    ; stdout
    int 0x80      ; call kernel

    mov eax, 3    ; sys_read
    mov ebx, 0    ; stdin
    mov ecx, buffer ; buffer to store input
    mov edx, 256  ; number of bytes to read
    int 0x80      ; call kernel

    mov ecx, helloMsg
    mov edx, helloLen
    mov eax, 4    ; sys_write
    mov ebx, 1    ; stdout
    int 0x80      ; call kernel

    mov ecx, buffer
    mov edx, 256  ; length of the input buffer
    mov eax, 4    ; sys_write
    mov ebx, 1    ; stdout
    int 0x80      ; call kernel

    mov eax, 1    ; sys_exit
    mov ebx, 0    ; exit code 
    int 0x80      ; call kernel