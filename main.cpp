#include "Image.h"
#include <iostream>
#include <string>

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

void negative(int height, int width) //creates an image with inverted colors.
{

	Image image(width, height);

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			image.SetColor(Color( (255 - ((float)x / (float)width)) , (255 - ( 1.0f - ( (float)x / (float)width) ) ) , (255 - ( (float)y / (float)height) )), x, y);
		}
	}

	image.Export("C:/Users/Matias/Desktop/imageN.bmp");
}

void read() {
	Image copy(0,0);
	copy.Import("C:/Users/Matias/Desktop/sample.bmp");
	int height = copy.getHeight();
	int width = copy.getWidth();
	
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			copy.SetNegativeColor(copy.GetColor(x, y), x, y);
		}
	}
	copy.Export("C:/Users/Matias/Desktop/dickmabutt.bmp");
}

int main() {
	read();

}

//path base para ir a escritorio:
//C:/Users/(usuario)/Desktop/(nombre).bmp

//Ejemplo en mi caso:
//C:/Users/porgois/Desktop/image.bmp

//Referencias:
//1) https://www.youtube.com/watch?v=vqT5j38bWGg&ab_channel=DesignedbyHugo
//2) https://www.youtube.com/watch?v=NcEE5xmpgQ0&t=56s&ab_channel=DesignedbyHugo

//------------------ISSUES-------------------------------------------
//hay un ligero error en exportar, distorsiona la imagen ligeramente.