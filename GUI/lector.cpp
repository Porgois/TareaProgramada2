#include "Image.h"
#include <string>
#include <vector>
#include <iostream>

//VARIABLES PARA COMUNICACION CON ENSAMBLADOR
std::vector<char> pixels;
int brillo_num = 0;
int iteraciones = 0;
//orden de las variables importa por algun motivo.

//VARIABLES EXTERNAS
std::vector<Color> vacio;
std::string path, file_name;
Image image;

extern "C" void BrilloAdd();
extern "C" void BrilloSub();
extern "C" void Negativo();
extern "C" void Contraste();

//Algoritmo para generar imagen "aleatoria".
void random(int height, int width) 
{
    Image image(width, height);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            image.SetColor(Color({ 255,0,0 }), x, y);
        }
    }
    image.Export("C:/Users/porgois/Desktop/papita.bmp");
}

//Algoritmos Traduccion.
void translateNasm(std::vector<char>& pixels, std::vector<Color>& colors)
{
    int size = colors.size() * 3;
    int counter = 0;
    int tres = 0;
 
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
}

void translateCPP(std::vector<char>& pixels, std::vector<Color>& colors) {
    int size = pixels.size();

    colors.resize(size / 3);
    int counter = 0;
    int tres = 0;

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
}

//Preguta ruta y nombre de archivo.
void ask() {
    std::cout << "Enter path: ";
    std::cin >> path;

    std::cout << "Enter file name: ";
    std::cin >> file_name;
}

//Filtros y Transformaciones.
void apply_brilloAdd(std::string path, std::string file_name, int brillo) {

    brillo_num = brillo;

    //Traductor para NASM <---> C++.
    translateNasm(pixels, image.getColors());

    BrilloAdd();

    //Traductor para C++ <---> NASM.
    translateCPP(pixels, vacio);
    
    //Apply new colors to image
    image.getColors() = vacio;

    //Export image with  newly-edited colors
    image.Export(path + file_name + "_edited.BMP");
}

void apply_brilloSub(int brillo) {

    brillo_num = brillo;

    //Traductor para NASM <---> C++.
    translateNasm(pixels, image.getColors());

    BrilloSub();

    //Traductor para C++ <---> NASM.
    translateCPP(pixels, vacio);

    //Apply new colors to image
    image.getColors() = vacio;

    //Export image with  newly-edited colors
    image.Export(path + file_name + "_edited.BMP");
}

void apply_negative(std::string path, std::string file_name) {

    //Traductor para NASM <---> C++.
    translateNasm(pixels, image.getColors());

    Negativo();

    std::cout << "negativo aplicado.\n";
    //Traductor para C++ <---> NASM.
    translateCPP(pixels, vacio);

    //Apply new colors to image
    image.getColors() = vacio;

    //Export image with  newly-edited colors
    image.Export(path + file_name + "_edited.BMP");
}

void apply_contrast(std::string path, std::string file_name) {

    //Traductor para NASM <---> C++.
    translateNasm(pixels, image.getColors());

    Contraste();

    //Traductor para C++ <---> NASM.
    translateCPP(pixels, vacio);

    //Apply new colors to image
    image.getColors() = vacio;

    //Export image with  newly-edited colors
    image.Export(path + file_name + "_edited.BMP");
}

//Lee la imagen.
Image read(std::string path, std::string file_name) {

    std::vector<Color> colors;

    image.Import(path + file_name + ".BMP");
    colors = image.getColors();

    int size = (colors.size() * 3);
    pixels.resize(size);

    //Traductor para NASM <---> C++.
    translateNasm(pixels, colors);

    //Calcular iteraciones para ensamblador.
    iteraciones = (size / 32);

    std::cout << "iteraciones: " << iteraciones << "\n";
    return image;
}

/*
path base para ir a escritorio:
C:/Users/porgois/Desktop/ [luego digitar nombre de archivo (sin extension)]

Referencias:
1) https://www.youtube.com/watch?v=vqT5j38bWGg&ab_channel=DesignedbyHugo
2) https://www.youtube.com/watch?v=NcEE5xmpgQ0&t=56s&ab_channel=DesignedbyHugo
*/
