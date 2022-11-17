bits 64
default rel

global _brillo
global _negativo
global _contraste
global _espejado
global _escalado

section .bss

	x resb 1
	y resb 33
	z resb 35

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
	
	mov r8b, 0
	for:
	
	vpaddusb ymm0, ymm0, ymm0
	
	inc r8b
	cmp r8b, 6
	jl for
	
	vmovups [rcx], ymm0
	ret
	
	_espejado:
	
	vmovups xmm0, [rcx+15]
	vmovups [rcx+16], xmm0
	vmovups ymm0, [rcx]
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
	VPSLLDQ ymm2, ymm2, 3
	vpor ymm2, ymm2, [z]
	VPSRLDQ ymm0, ymm0, 3
	
	inc r9b
	cmp r9b, 5
	jl ciclo
	
	vmovups [rcx], ymm2
	vmovups xmm1, [rcx]
	vmovups xmm2, [rcx+16]
	vmovups [rcx], xmm2
	vmovups [rcx+15], xmm1
	
	_escalado:
	
	ret
	