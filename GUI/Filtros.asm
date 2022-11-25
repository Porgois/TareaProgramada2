bits 64
default rel

;funciones para utilizar en C++
global BrilloAdd
global BrilloSub
global Negativo
global Contraste
global Espejado

section .data 
        extern pixels, iteraciones, brillo_num ;esta es la cantidad de brillo.
	
section .bss
	neg: resb 1
	con1: resb 1
	con2: resb 2

section .text
;----------Inicializacion------------.
        inicializar:
            xor rcx, rcx
            xor r9, r9 ;a r9 se le suma 32 bytes cada iteracion (offset).
            xor r8, r8

            mov rcx, [pixels] ;se mueve el vector de chars "pixels" para ser editado.
            mov r8, [iteraciones] ;para ver cuantas veces tiene que correr el loop.
            ret

;----------Brillo(+)------------.
	brightenAdd:
		vmovups ymm0, [rcx + r9]
		vpbroadcastb ymm1, [brillo_num]
		vpaddusb ymm2, ymm1, ymm0
		vmovups [rcx + r9], ymm2

		add r9, byte 32
		dec r8
		jmp loopBrilloAdd

	BrilloAdd:
		call inicializar
		jmp loopBrilloAdd

	loopBrilloAdd:
		cmp r8, byte 0
		je terminar
		jne brightenAdd
		
;----------Brillo(-)------------.
	brightenSub:
		vmovups ymm0, [rcx + r9]
		vpbroadcastb ymm1, [brillo_num]
		vpsubusb ymm2, ymm0, ymm1
		vmovups [rcx + r9], ymm2

		add r9, byte 32
		dec r8
		jmp loopBrilloSub

	BrilloSub:
		call inicializar
		jmp loopBrilloSub

	loopBrilloSub:
		cmp r8, byte 0
		je terminar
		jne brightenSub
		
;---------Negativo------------.	
	negative:
                vmovups ymm0, [rcx + r9]
                vpbroadcastb ymm1, [neg]
		vpsubusb ymm2, ymm1, ymm0
                vmovups [rcx + r9], ymm2
		
		add r9, byte 32
		dec r8
		jmp loopNegativo
	
	Negativo:
                call inicializar
                mov r11b, 255
                mov [neg], r11b
		jmp loopNegativo

	loopNegativo:
		cmp r8, byte 0
		je terminar
		jne negative

;--------Contraste------------.
	contrast:
		vmovups ymm0, [rcx + r9]
		vpbroadcastb ymm1, [con1]
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
                mov r11b, 128
                mov [con1], r11b

                mov r10b, 2
		mov [con2], r10b
		jmp loopContraste
		
	loopContraste:
		cmp r8, byte 0
		je terminar
		jne contrast

;----------Espejado---------------.

    Espejado:
		;call inicializar
		;mov rbx, [pixels + iteraciones - 1] (se determina que tiene que ir en orden inverso).
		;loop:
		;la idea es que vaya metiendo lo de rbx en rcx (orden inverso).
         ret
;---------------------------------.

	terminar:
          ret
