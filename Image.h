#pragma once
#include <vector>

struct Color {
	float r, g, b;

	Color();
	Color(float r, float g, float b);
	~Color();

};
class Image {
public:
	Image(int width, int height);
	~Image();

	Color GetColor(int x, int y) const;
	void SetColor(const Color& color, int x, int y);
	void SetNegativeColor(const Color& color, int x, int y);

	void Import(const char* path);
	void Export(const char* path) const;
	int getHeight();
	int getWidth();

private:
	int m_width;
	int m_height;
	std::vector<Color> m_colors;
};


//Referencias:
//1) https://www.youtube.com/watch?v=vqT5j38bWGg&ab_channel=DesignedbyHugo
//2) https://www.youtube.com/watch?v=NcEE5xmpgQ0&t=56s&ab_channel=DesignedbyHugo
