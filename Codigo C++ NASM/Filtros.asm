bits 64
default rel

global Brillo ;funciones para utilizar en C++

section .bss

section .data ;
	extern pixels, iteraciones, brillo_num ;esta es la cantidad de brillo por la que se suma.
	
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

	terminar:
		ret