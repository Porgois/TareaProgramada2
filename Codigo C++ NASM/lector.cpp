#include "Image.h"
#include <string>
#include <vector>
#include <iostream>

//VARIABLES PARA COMUNICACION CON ENSAMBLADOR
std::vector<char> pixels;
int brillo_num = 0;
int iteraciones = 0;
//por algun motivo que alguien me tiene que explicar, el orden de esta mierda es importante. Si le pone el iteraciones arriba de cualquier otra variable (parece que es la de brillo_num), se va a la absoluta basura.

//VARIABLES EXTERNAS
std::vector<Color> vacio;
std::string path, file_name;
Image image;

extern "C" void Brillo();
extern "C" void Negativo();
extern "C" void Contrast();

//Algoritmo para generar imagen "aleatoria".
void random(int height, int width) //creates an image with random colors.
{
    Image image(width, height);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            image.SetColor(Color({ 255,0,0 }), x, y);
        }
    }
    image.Export("C:/Users/porgois/Desktop/papita.bmp");
}

/* Esto hay que borrarlo
//Este es un algoritmo de prueba.
void negative(std::vector<char>& pixeles) //creates an image with inverted colors.
{
    int size = pixeles.size();
    for (int i = 0; i < size; i++) {
        pixeles[i] = 255 - pixeles[i];
    }
}
*/

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
void apply_brillo(int brillo) {

    brillo_num = brillo;

    //Traductor para NASM <---> C++.
    translateNasm(pixels, image.getColors());

    Brillo();

    //Traductor para C++ <---> NASM.
    translateCPP(pixels, vacio);
    
    //Apply new colors to image
    image.getColors() = vacio;

    //Export image with  newly-edited colors
    image.Export(path + file_name + "_brillo.BMP");
}

void apply_negative() {

    //Traductor para NASM <---> C++.
    translateNasm(pixels, image.getColors());

    Negativo();

    //Traductor para C++ <---> NASM.
    translateCPP(pixels, vacio);

    //Apply new colors to image
    image.getColors() = vacio;

    //Export image with  newly-edited colors
    image.Export(path + file_name + "_edited.bmp");
}

void apply_contrast() {

    //Traductor para NASM <---> C++.
    translateNasm(pixels, image.getColors());

    Contrast();

    //Traductor para C++ <---> NASM.
    translateCPP(pixels, vacio);

    //Apply new colors to image
    image.getColors() = vacio;

    //Export image with  newly-edited colors
    image.Export(path + file_name + "_edited.bmp");
}

//Lee la imagen.
Image read(std::string path, std::string file_name) {

    std::vector<Color> colors;

    image.Import(path + file_name + ".bmp");
    colors = image.getColors();

    int size = (colors.size() * 3);
    pixels.resize(size);

    //Traductor para NASM <---> C++.
    translateNasm(pixels, colors);

    //Calcular iteraciones para ensamblador.
    iteraciones = (size / 32);
    
    return image;
}

int main(){
    read("C:/Users/porgois/Desktop/", "red");
    apply_brillo(120);
}
/*
path base para ir a escritorio:
C:/Users/porgois/Desktop/ [luego digitar nombre de archivo (sin extension)]

Referencias:
1) https://www.youtube.com/watch?v=vqT5j38bWGg&ab_channel=DesignedbyHugo
2) https://www.youtube.com/watch?v=NcEE5xmpgQ0&t=56s&ab_channel=DesignedbyHugo
*/
