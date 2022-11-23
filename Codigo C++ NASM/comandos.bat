nasm -f win64 Filtros.asm -o Filtros.obj
g++ .\Image.cpp .\Image.h .\lector.cpp .\Filtros.obj -o porga.exe -no-pie