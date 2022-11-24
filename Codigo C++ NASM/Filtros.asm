bits 64
default rel

;funciones para utilizar en C++
global Brillo 
global Negativo
global Contraste

section .data ;
	extern pixels, iteraciones, brillo_num, contraste_num ;esta es la cantidad de brillo y constraste.
	
section .bss
	neg resb 1

section .text

;----------Inicializacion------------.
	inicializar: ;inicializa todos los valores necesarios
		mov rcx, [pixels] ;se mueve el vector de chars "pixels" para ser editado.
		xor r8, r8 
		xor r9, r9 ;a r9 se le suma 32 bytes cada iteracion (offset).
		mov r8, [iteraciones] ;para ver cuantas veces tiene que correr el loop.
		inc r8 ;iteracion extra para los pixeles sobrantes.
		ret

;----------Brillo------------.
	brighten:
		vmovups ymm0, [rcx + r9]
		vpbroadcastb ymm1, [brillo_num]
		vpaddusb ymm2, ymm1, ymm0
		vmovups [rcx + r9], ymm2

		add r9, byte 32
		dec r8
		jmp loopBrillo

	Brillo:
		call inicializar
		jmp loopBrillo

	loopBrillo:
		cmp r8, byte 0
		je terminar
		jne brighten
		
;---------Negativo------------.	
	negative:
		vmovups ymm0, [rcx + r9]
		mov r8b, 255
		mov [neg], r8b
		vpbroadcastb ymm1, [neg]
		vpsubusb ymm2, ymm1, ymm0
		vmovups [rcx + r9], ymm2
		
		add r9, byte 32
		dec r8
		jmp loopNegativo
	
	Negativo:
		call inicializar
		jmp loopNegativo

	loopNegativo:
		cmp r8, byte 0
		je terminar
		jne negative

;--------Contraste------------.
	contrast:
		vmovups ymm0, [rcx + r9]
		mov r8b, 128
		mov [con1], r8b
		vpbroadcastb ymm1, [con1]
		mov r9b, 2
		mov [con1], r9b
		vpbroadcastb ymm2, [con2]
		vpsubusb ymm3, ymm0, ymm1
		vpmullw ymm3, ymm3, ymm2
		vpaddusb ymm3, ymm3, ymm1
		vmovups [rcx + r9], ymm3

		add r9, byte 32
		dec r8
		jmp loopContraste
		
	Contraste:
		call inicializar
		jmp loopContraste
		
	loopContraste:
		cmp r8, byte 0
		je terminar
		jne contrast
		
;----------Espejado---------------.

	terminar:
		ret