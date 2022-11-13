%macro print 2
  mov rax, 1
  mov rdi, 1
  mov rsi, %1
  mov rdx, %2
  syscall
%endmacro

%macro input 2
  mov rax, 0
  mov rdi, 1
  mov rsi, %1
  mov rdx, %2
  syscall
%endmacro

%macro ind 2 ;mueve a r8b para comparar sin el Enter.
mov %1, [%2]
sub %1, 48
mov [%2], %1
mov %1, %2
mov r8b, [%1]
%endmacro

%macro exit 0
  mov rax, 60
  mov rdi, 0
  syscall
%endmacro