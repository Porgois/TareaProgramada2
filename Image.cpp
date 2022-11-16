#include "Image.h"
#include <iostream>
#include <fstream>

Color::Color()
	:r(0), g(0), b(0)
{
}

Color::Color(float r, float g, float b)
	: r(r), g(g), b(b)
{
}

Color::~Color()
{
}

Image::Image(int width, int height)
	: m_width(width), m_height(height), m_colors(std::vector<Color>(width* height))
{
}

Image::Image()
	:m_width(0), m_height(0)
{
	
}

Image::~Image()
{
}

Color Image::GetColor(int x, int y) const
{
	return m_colors[y * m_width + x];
}

void Image::SetColor(const Color& color, int x, int y)
{
	m_colors[y * m_width + x].r = color.r;
	m_colors[y * m_width + x].g = color.g;
	m_colors[y * m_width + x].b = color.b;
}

void Image::SetNegativeColor(const Color& color, int x, int y)
{
	m_colors[y * m_width + x].r = 255 - color.r;
	m_colors[y * m_width + x].g = 255 - color.g;
	m_colors[y * m_width + x].b = 255 - color.b;
}

void Image::Import(std::string path)
{
	std::ifstream file;
	file.open(path, std::ios::in | std::ios::binary);

	if (!file.is_open()) {
		std::cout << "The file could not be opened.\n";
		exit(0);
	}

	const int fileHeaderSize = 14;
	const int informationHeaderSize = 40;

	unsigned char fileHeader[fileHeaderSize];
	file.read(reinterpret_cast<char*>(fileHeader), fileHeaderSize);

	//check if the file is .bmp (bitmap image).
	if (fileHeader[0] != 'B' || fileHeader[1] != 'M') {
		std::cout << "The selected file is not a bitmap image.\n";
		file.close();
		exit(0);
	}

	unsigned char informationHeader[informationHeaderSize];
	file.read(reinterpret_cast<char*>(informationHeader), informationHeaderSize);

	int fileSize = fileHeader[2] + (fileHeader[3] << 8) + (fileHeader[4] << 16) + (fileHeader[5] << 24); //stored in fileheader #2. 

	m_width = informationHeader[4] + (informationHeader[5] << 8) + (informationHeader[6] << 16) + (informationHeader[7] << 24);
	m_height = informationHeader[8] + (informationHeader[9] << 8) + (informationHeader[10] << 16) + (informationHeader[11] << 24);

	m_colors.resize(m_width * m_height);

	const int paddingAmount = ((4 - (m_width * 3) % 4) % 4);

	for (int y = 0; y < m_height; y++) {
		for (int x = 0; x < m_width; x++) {
			unsigned char color[3];
			file.read(reinterpret_cast<char*>(color), 3);
			m_colors[y * m_width + x].r = static_cast<float>(color[2]) / 255.0f;
			m_colors[y * m_width + x].g = static_cast<float>(color[1]) / 255.0f;
			m_colors[y * m_width + x].b = static_cast<float>(color[0]) / 255.0f;
		}
		file.ignore(paddingAmount);
	}
	file.close();
	std::cout << "File succesfuly read.\n";
}

void Image::Export(std::string path) const
{
	std::ofstream file;

	file.open(path, std::ios::out | std::ios::binary);

	if (!file.is_open()) {
		std::cout << "file could not be opened.\n";
		exit(0);
	}

	unsigned char bmpPad[] = { 0, 0, 0 };
	const int paddingAmount = ((4 - (m_width * 3) % 4) % 4);

	const int fileHeaderSize = 14;
	const int informationHeaderSize = 40;
	const int fileSize = fileHeaderSize + informationHeaderSize + m_width * m_height * 3 + paddingAmount * m_height;

	unsigned char fileHeader[fileHeaderSize];

	//file type
	fileHeader[0] = 'B';
	fileHeader[1] = 'M';

	//reserved 1 (not used)
	fileHeader[2] = fileSize;
	fileHeader[3] = fileSize >> 8;
	fileHeader[4] = fileSize >> 16;
	fileHeader[5] = fileSize >> 24;

	//reserved 2 (not used)
	fileHeader[6] = 0;
	fileHeader[7] = 0;
	fileHeader[8] = 0;
	fileHeader[9] = 0;

	//pixel data offset
	fileHeader[10] = fileHeaderSize + informationHeaderSize;
	fileHeader[11] = 0;
	fileHeader[12] = 0;
	fileHeader[13] = 0;

	unsigned char informationHeader[informationHeaderSize];

	//header size
	informationHeader[0] = informationHeaderSize;
	informationHeader[1] = 0;
	informationHeader[2] = 0;
	informationHeader[3] = 0;

	//image width
	informationHeader[4] = m_width;
	informationHeader[5] = m_width >> 8;
	informationHeader[6] = m_width >> 16;
	informationHeader[7] = m_width >> 24;

	//image height
	informationHeader[8] = m_height;
	informationHeader[9] = m_height >> 8;
	informationHeader[10] = m_height >> 16;
	informationHeader[11] = m_height >> 24;

	//planes
	informationHeader[12] = 1;
	informationHeader[13] = 0;

	//bits per pixel (RGB)
	informationHeader[14] = 24;
	informationHeader[15] = 0;

	//compression (no compression)
	informationHeader[16] = 0;
	informationHeader[17] = 0;
	informationHeader[18] = 0;
	informationHeader[19] = 0;

	//image size (no compression)
	informationHeader[20] = 0;
	informationHeader[21] = 0;
	informationHeader[22] = 0;
	informationHeader[23] = 0;

	// x pixels per meter (not specified)
	informationHeader[24] = 0;
	informationHeader[25] = 0;
	informationHeader[26] = 0;
	informationHeader[27] = 0;

	// y pixels per meter (not specified)
	informationHeader[28] = 0;
	informationHeader[29] = 0;
	informationHeader[30] = 0;
	informationHeader[31] = 0;

	//total colors (color palette not used)
	informationHeader[32] = 0;
	informationHeader[33] = 0;
	informationHeader[34] = 0;
	informationHeader[35] = 0;

	//important colors (generally ignored)
	informationHeader[36] = 0;
	informationHeader[37] = 0;
	informationHeader[38] = 0;
	informationHeader[39] = 0;

	file.write(reinterpret_cast<char*> (fileHeader), fileHeaderSize);
	file.write(reinterpret_cast<char*>(informationHeader), informationHeaderSize);

	for (int y = 0; y < m_height; y++) {
		for (int x = 0; x < m_width; x++) {
			unsigned char r = static_cast<unsigned char>(GetColor(x, y).r * 255.0f);
			unsigned char g = static_cast<unsigned char>(GetColor(x, y).g * 255.0f);
			unsigned char b = static_cast<unsigned char>(GetColor(x, y).b * 255.0f);

			unsigned char color[] = { b, g ,r };

			file.write(reinterpret_cast<char*>(color), 3);
		}
		file.write(reinterpret_cast<char*>(bmpPad), paddingAmount);
	}

	file.close();

	std::cout << "file was created.\n";
}

int Image::getHeight()
{
	return m_height;
}

int Image::getWidth()
{
	return m_width;
}

std::vector<Color> Image::getColors()
{
	return this->m_colors;
}

//Referencias:
//1) https://www.youtube.com/watch?v=vqT5j38bWGg&ab_channel=DesignedbyHugo
//2) https://www.youtube.com/watch?v=NcEE5xmpgQ0&t=56s&ab_channel=DesignedbyHugo
