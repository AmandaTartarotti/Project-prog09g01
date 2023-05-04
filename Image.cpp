/*

An Image object represents an image. It has an associated width (width()) and height (height()), and must hold a 2D matrix of colors 
with these dimensions. Each (x, y) position in this matrix, where 0 <= x < width() and 0 <= y < height(), is called a pixel. 
Pixel (0,0) corresponds to the upper-left corner of the image, and pixel (width() - 1, height() - 1) corresponds to 
the lower-right corner of the image.

*/

#include "Image.hpp"

namespace prog
{
  Image::Image(int w, int h, const Color &fill): width_(w), height_(h), pixels_ (new Color *[h]) // Create image with width w, height h, and all pixels set to color fill.
  {
    for (int i = 0; i < h; i++){ //enquanto i for menor que height
      pixels_[i] = new Color[w]; // aloca memória em uma nova linha com width w
      for (int j = 0; j < w; j++){ 
        pixels_[i][j] = fill; // Atribui a fill color para o pixel em questão
      }
    }
  }
  Image::~Image() // If you use dynamically allocated memory explicitly, the destructor should take care of releasing that memory
  {
    for (int i = 0; i < height_; i++){

      delete[] pixels_[i];
    }
    delete[] pixels_;
  }
  int Image::width() const // Get image width.
  {
    return width_;
  }
  int Image::height() const // Get image height.
  {
    return height_;
  }

  Color& Image::at(int x, int y) // Get mutable reference to the value of pixel (x, y), where 0 <= x < width() and 0 <= y < height()
  {
    return pixels_[x][y];
  }

  const Color& Image::at(int x, int y) const // Get read-only reference to the value of pixel (x, y).
  {
    return pixels_[x][y]; // const retorna uma referência somente leitura
  }
}
