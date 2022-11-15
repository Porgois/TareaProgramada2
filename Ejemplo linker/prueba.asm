global _print

section .data
    msg: db "Hola", 0xa
    msg_len: equ $-msg

section .text
_print:
    mov rax, 5
    ret

    ;esto es para llamar la mierda
    
    ;print msg
    mov rax, 1
    mov rdi, 1
    mov rsi, msg
    mov rdx, msg_len
    syscall

    ;exit
    mov rax, 60
    mov rdi, 1
    syscall
