#include "Image.h"
#include <iostream>
#include <string>
#include <vector>

void random(int height, int width) //creates an image with random colors.
{

	Image image(width, height);

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			image.SetColor(Color((float)x / (float)width, 1.0f - ((float)x / (float)width), (float)y / (float)height), x, y);
		}
	}

	image.Export("C:/Users/Matias/Desktop/imageR.bmp");
}

void negative(int height, int width, Image* image) //creates an image with inverted colors.
{
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			image->SetNegativeColor(image->GetColor(x, y), x, y);
		}
	}
}

void ask(std::string* path, std::string* file_name) {
	std::cout << "Enter path: ";
	std::cin >> *path;

	std::cout << "Enter file name: ";
	std::cin >> *file_name;
}


void read() {
	std::string path, file_name;
	std::vector<Color> colores;
	ask(&path, &file_name);

	int arr[32]; //32 porque es lo que cabe en ymm. 

	/*
		en ese array es que se tienen que meter los colores.
		puede ser como:
		int arr[32];
		colores[0].r = arr[0]
		colores[0].g = arr[1]
		colores[0].b = arr[2]
		...
		hasta llegar a 32.

		SE HACE EL CASTEO DE ESTA FORMA: arr[0] = static_cast<int>(colores[0].r)
	*/
	Image copy;

	//copy.Import("C:/Users/porgois/Desktop/sample.bmp");
	copy.Import(path + file_name + ".bmp");
	int height = copy.getHeight();
	int width = copy.getWidth();
	
	std::cout << "Dimensiones: [" << height << " X " << width << "].\n";

	negative(height, width, &copy);

	colores = copy.getColors();
	std::cout << "Valor rojo del primer valor del vector de colores:\n";
	std::cout << colores[58].r << "\n";

	copy.Export(path  + file_name + "_negative.bmp");
}

int main() {
	read();
}

//path base para ir a escritorio:
//C:/Users/(usuario)/Desktop/(nombre).bmp

//Ejemplo en mi caso:
//C:/Users/porgois/Desktop/sample.bmp

//Referencias:
//1) https://www.youtube.com/watch?v=vqT5j38bWGg&ab_channel=DesignedbyHugo
//2) https://www.youtube.com/watch?v=NcEE5xmpgQ0&t=56s&ab_channel=DesignedbyHugo

//------------------ISSUES-------------------------------------------
//hay un ligero error en exportar, distorsiona la imagen ligeramente.