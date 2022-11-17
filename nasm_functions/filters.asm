bits 64
default rel

global _brillo
global _negativo
global _contraste
global _espejado
;global _escalado

section .data

section .bss
	x resb 1
	y resb 33
	z resb 32

section .text
	
	_brillo:
	
	vmovups ymm0, [rcx]
	mov [x], byte 10
	vpbroadcastb ymm1, [x]
	vpaddusb ymm2, ymm1, ymm0
	vmovups [rcx], ymm2
	ret
	
	_negativo:
	
	vmovups ymm0, [rcx]
	mov r8b, 255
	mov [x], r8b
	vpbroadcastb ymm1, [x]
	vpaddusb ymm2, ymm1, ymm0
	vmovups [rcx], ymm2
	ret
	
	_contraste:
	
	vmovups ymm0, [rcx]
	mov [x], byte 5
	vpbroadcastb ymm1, [x]
	vpmuludq ymm2, ymm1, ymm0
	mov [x], byte 10
	vpbroadcastb ymm1, [x]
	vpaddusb ymm2, ymm1, ymm2
	vmovups [rcx], ymm2
	ret
	
	_espejado:
	
	vmovups xmm0, [rdi+15]
	vmovups [rdi+16], xmm0
	vmovups ymm0, [rdi]
	mov r8b, 0
	mov [y], r8b
	vpbroadcastb ymm2, [y]
	vpbroadcastb ymm1, [y]
	
	mov r9b, 0
	
	ciclo:
	vmovups [z], ymm0
	vmovups xmm3, [z+16]
	vmovups [z+3], ymm1
	vmovups [z+16], xmm3
	vmovups [z+19], xmm1
	VPSLLQ ymm2, ymm2, 3
	
	;_escalado:
	
	
	