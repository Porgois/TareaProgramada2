#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
#include <string>

struct Color {
    float r, g, b;

    Color();
    Color(float r, float g, float b);
    ~Color();
};

class Image {
public:
    Image(int width, int height);
    Image();
    ~Image();

    Color GetColor(int x, int y) const;
    void SetColor(const Color& color, int x, int y);

    void Import(std::string path);
    void Export(std::string path) const;
    int getHeight();
    int getWidth();
    std::vector<Color>& getColors();

private:
    int m_width;
    int m_height;
    std::vector<Color> m_colors;
};

//Referencias:
//1) https://www.youtube.com/watch?v=vqT5j38bWGg&ab_channel=DesignedbyHugo
//2) https://www.youtube.com/watch?v=NcEE5xmpgQ0&t=56s&ab_channel=DesignedbyHugo

#endif // IMAGE_H
