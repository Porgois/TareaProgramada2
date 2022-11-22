#pragma once
#include "Image.h"
#include <iostream>
#include <string>
#include <vector>

//VARIABLES PARA COMUNICACION CON ENSAMBLADOR
std::vector<char> pixels;
char pixeles[32];

//VARIABLES EXTERNAS
std::vector<Color> vacio;
Image image;

//Algoritmo para generar imagen "aleatoria".
void random(int height, int width) //creates an image with random colors.
{
    Image image(width, height);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            image.SetColor(Color({255,0,0}), x, y);
        }
    }
    image.Export("C:/Users/porgois/Desktop/papita.bmp");
}

//Este es un algoritmo de prueba.
void negative(std::vector<char>& pixeles) //creates an image with inverted colors.
{
    size_t size = pixeles.size();
    for (int i = 0; i < size; i++) {
        pixeles[i] = 255 - pixeles[i];
    }
}

//Algoritmos Traduccion.
void translateNasm(std::vector<char>& pixels, std::vector<Color>& colors)
{
    size_t size = colors.size() * 3;
    int counter = 0;
    int tres = 0;

    std::cout << "Creando arreglo integers...\n";

    for (int i = 0; i < size; i++)
    {
        switch (tres)
        {
            case 0:
                pixels[i] = static_cast<char>(colors[counter].r);
                tres++;
                break;
            case 1:
                pixels[i] = static_cast<char>(colors[counter].g);
                tres++;
                break;
            case 2:
                pixels[i] = static_cast<char>(colors[counter].b);
                counter++;
                tres = 0;
                break;
        }
    }

    std::cout << "Arreglo creado!\n";
}

void translateCPP(std::vector<char>& pixels, std::vector<Color>& colors) {
    size_t size = pixels.size();

    colors.resize(size / 3);
    int counter = 0;
    int tres = 0;

    std::cout << "Creando vector colores...\n";

    for (int i = 0; i < size; ++i) {
        switch (tres) {
            case(0):
                colors[counter].r = static_cast<float>(pixels[i]);
                tres++;
                break;
            case(1):
                colors[counter].g = static_cast<float>(pixels[i]);
                tres++;
                break;
            case(2):
                colors[counter].b = static_cast<float>(pixels[i]);
                tres = 0;
                counter++;
        }
    }
    std::cout << "Vector creado!" << "\n";
}

//Preguta ruta y nombre de archivo.
void ask(std::string* path, std::string* file_name) {
    std::cout << "Enter path: ";
    std::cin >> *path;

    std::cout << "Enter file name: ";
    std::cin >> *file_name;
}

void apply_negative(std::string path, std::string file_name){
    //Filtro (Esto va en NASM)
    negative(pixels);

    //Traductor para C++ <---> NASM.
    translateCPP(pixels, vacio);

    //Apply new colors to image
    image.getColors() = vacio;

    //Export image with  newly-edited colors
    image.Export(path  + file_name + "_edited.bmp");
}

//divide el vector pixels grande a uno de 32 bytes llamado pixeles. [implementacion conceptual]
void toNasm(int index){
    for(int i = index; i < 32; ++i){
        pixeles[i] = pixels[i];
    }
}

//Lee la imagen y ejecuta los algoritmos principales.
Image read(std::string path, std::string file_name) {

    std::vector<Color> colors;

    image.Import(path + file_name + ".bmp");
    colors = image.getColors();

    size_t size = (colors.size() * 3);
    pixels.resize(size);

    //Traductor para NASM <---> C++.
    translateNasm(pixels, colors);

    return image;
}

/*
path base para ir a escritorio:
C:/Users/porgois/Desktop/ [luego digitar nombre de archivo (sin extension)]

Referencias:
1) https://www.youtube.com/watch?v=vqT5j38bWGg&ab_channel=DesignedbyHugo
2) https://www.youtube.com/watch?v=NcEE5xmpgQ0&t=56s&ab_channel=DesignedbyHugo
*/
