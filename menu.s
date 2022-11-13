%include "macros.s"
global _start

section .bss
reply: resb 2

section .data
  msg: db "---Menu---",0xa, "Digite [1] para aplicar filtro Negativo.",0xa
  msg_len: equ $-msg

  msg2: db "*Aplicado Filtro Negativo*", 0xa
  msg2_len: equ $-msg2

section .text

_start:
  print msg, msg_len
  input reply, 2
  ind r8, reply
  call compares
  exit

compares:
  cmp r8b, 1 ;compara con 1 para aplicar filtro negativo.
  je negativo
  ret

negativo:
  print msg2, msg2_len
  ret


