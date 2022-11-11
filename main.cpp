#include "Image.h"
#include <iostream>
#include <string>

int main() {
	const int width = 640;
	const int height = 480;

	Image image(width, height);

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			image.SetColor(Color((float)x / (float)width, 1.0f - ((float)x / (float)width), (float)y / (float)height), x, y);
			
		}
	
	}

	image.Export("C:/Users/porgois/Desktop/image.bmp");
}

//path base para ir a escritorio:
//C:/Users/(usuario)/Desktop/(nombre).bmp

//Ejemplo en mi caso:
//C:/Users/porgois/Desktop/image.bmp