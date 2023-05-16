#include "Image.hpp"
#include <cstddef>

namespace prog
{
  Image::Image(int w, int h, const Color &fill)
  {
    width_ = w, height_ = h;

    pixels = new Color *[width_];
    for (int i = 0; i < width_; i++)
    {
      pixels[i] = new Color[height_];
    }

    for (int i = 0; i < width_; i++)
    {
      for (int j = 0; j < height_; j++)
      {
        pixels[i][j] = fill;
      }
    }
  }
  Image::~Image()
  {
    for (int i = 0; i < width_; i++)
    {
      delete[] pixels[i]; // delete stored pointer
    }

    delete[] pixels; // delete sub array
    pixels = NULL;
  }
  int Image::width() const
  {
    return width_;
  }
  int Image::height() const
  {
    return height_;
  }

  Color &Image::at(int x, int y)
  {
    return pixels[x][y];
  }

  const Color &Image::at(int x, int y) const
  {
    return pixels[x][y];
  }

  void Image::invert()
  {
    for (int i = 0; i < width_; i++)
    {
      for (int j = 0; j < height_; j++)
      {
        pixels[i][j].invert();
      }
    }
  }

  void Image::to_gray_scale()
  {
    for (int i = 0; i < width_; i++)
    {
      for (int j = 0; j < height_; j++)
      {
        pixels[i][j].to_gray_scale();
      }
    }
  }

  void Image::replace(const Color& a, const Color& b) {
      for(int i = 0; i < width_; i++)
        {
            for(int j = 0; j < height_; j++)
            {
                if (pixels[i][j] == a)
                    pixels[i][j] = b;
            }
        }
  }


}
