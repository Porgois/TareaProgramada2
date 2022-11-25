#include "Image.h"
#include <string>
#include <vector>
#include <iostream>

//VARIABLES PARA COMUNICACION CON ENSAMBLADOR
std::vector<char> pixels;
int brillo_num = 0;

//VARIABLES EXTERNAS
std::vector<Color> vacio;
std::string path, name;
Image image;

//Iteraciones (esta variable tiene que ir al final o todo se cae).
int iteraciones = 0;

extern "C" void BrilloAdd();
extern "C" void BrilloSub();
extern "C" void Negativo();
extern "C" void Contraste();
extern "C" void Espejado();

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

//Filtros y Transformaciones.
void apply_brilloAdd(int brillo) {

    brillo_num = brillo;

    //Traductor para NASM <---> C++.
    translateNasm(pixels, image.getColors());

    BrilloAdd();

    //Traductor para C++ <---> NASM.
    translateCPP(pixels, vacio);
    
    //Apply new colors to image
    image.getColors() = vacio;

    //Export image with newly-edited colors.
    image.Export(path + name + "_edited.BMP");
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

    //Export image with newly-edited colors.
    image.Export(path + name + "_edited.BMP");
}

//これは関数を7回繰り返します
void apply_negative() {

    //Traductor para NASM <---> C++.
    translateNasm(pixels, image.getColors());

    Negativo();

    //Traductor para C++ <---> NASM.
    translateCPP(pixels, vacio);

    //Apply new colors to image
    image.getColors() = vacio;

     //Export image with newly-edited colors.
    image.Export(path + name + "_edited.BMP");
}

//аюда пор фаворит
void apply_contrast() {

    //Traductor para NASM <---> C++.
    translateNasm(pixels, image.getColors());

    Contraste();

    //Traductor para C++ <---> NASM.
    translateCPP(pixels, vacio);

    //Apply new colors to image
    image.getColors() = vacio;

    //Export image with newly-edited colors.
    image.Export(path + name + "_edited.BMP");
}

//nie mogę już tego robić
void apply_espejado(){

    //Traductor para NASM <---> C++.
    translateNasm(pixels, image.getColors());

    Espejado();

    //Traductor para C++ <---> NASM.
    translateCPP(pixels, vacio);

    //Apply new colors to image
    image.getColors() = vacio;

    //Export image with newly-edited colors.
    image.Export(path + name + "_edited.BMP");

}

//Lee la imagen.
Image read() {

    std::vector<Color> colors;

    image.Import(path + name + ".BMP");
    colors = image.getColors();

    int size = (colors.size() * 3);
    pixels.resize(size);

    //Traductor para NASM <---> C++.
    translateNasm(pixels, colors);

    //Calcular iteraciones para ensamblador.
    iteraciones = (size / 32);

    return image;
}

/*
Referencias:
1) https://www.youtube.com/watch?v=vqT5j38bWGg&ab_channel=DesignedbyHugo
2) https://www.youtube.com/watch?v=NcEE5xmpgQ0&t=56s&ab_channel=DesignedbyHugo
*/
