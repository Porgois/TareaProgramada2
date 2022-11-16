#include "Image.h"
#include <iostream>
#include <string>
#include <vector>

int* arr;
std::vector<Color> colores;

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

void translateNasm() {
	int size = colores.size() * 3;
	int counter = 0;
	int tres = 0;

	std::cout << "Creando arreglo integers... para NASM\n";
	for (int i = 0; i < size; i++) 
	{
		switch (tres) 
		{
			case 0:
				arr[i] = static_cast<int>(colores[counter].r);
				tres++;
				break;
			case 1:
				arr[i] = static_cast<int>(colores[counter].g);
				tres++;
				break;
			case 2:
				arr[i] = static_cast<int>(colores[counter].b);
				counter++;
				tres = 0;
				break;
		}
	}
	std::cout << "Arreglo creado Satisfactoriamente!\n";
}

void translateCPP(int arr[], std::vector<Color> &colors, int size) {
	std::vector<Color> colores;
	colores.resize(size / 3);
	int counter = 0;
	int tres = 0;

	std::cout << "Creando vector colores... para C++\n";
	for (int i = 0; i < size; ++i) {
		switch (tres) {
			case(0):
				colores[counter].r = static_cast<float>(arr[i]);
				tres++;
				break;
			case(1):
				colores[counter].g = static_cast<float>(arr[i]);
				tres++;
				break;
			case(2):
				colores[counter].b = static_cast<float>(arr[i]);
				tres = 0;
				counter++;
		}
	}
	std::cout << "Vector creado!" << "\n";
}

void ask(std::string* path, std::string* file_name) {
	std::cout << "Enter path: ";
	std::cin >> *path;

	std::cout << "Enter file name: ";
	std::cin >> *file_name;
}

void read() {
	std::string path, file_name;
	ask(&path, &file_name);

	Image copy;
	copy.Import(path + file_name + ".bmp");
	int height = copy.getHeight();
	int width = copy.getWidth();
	
	std::cout << "Dimensiones Imagen: [" << height << " X " << width << "].\n";
	copy.Export(path  + file_name + "_read.bmp");

}

int main() {
	read();
}

//path base para ir a escritorio:
//C:/Users/(usuario)/Desktop/(nombre).bmp

//Ejemplo en mi caso:
//C:/Users/porgois/Desktop/sample.bmp

//copy.Import("C:/Users/porgois/Desktop/sample.bmp");

//int arr[32]; //32 porque es lo que cabe en ymm. 
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

		*en esto se basan las funciones de  translateNASM y translateCPP
	*/

//Referencias:
//1) https://www.youtube.com/watch?v=vqT5j38bWGg&ab_channel=DesignedbyHugo
//2) https://www.youtube.com/watch?v=NcEE5xmpgQ0&t=56s&ab_channel=DesignedbyHugo
