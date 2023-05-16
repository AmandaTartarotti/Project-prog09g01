#include "Image.hpp"
#include <cstddef>
using namespace std;

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

  void Image::replace(const Color &a, const Color &b)
  {
    for (int i = 0; i < width_; i++)
    {
      for (int j = 0; j < height_; j++)
      {
        if (pixels[i][j] == a)
          pixels[i][j] = b;
      }
    }
  }

  void Image::fill(int x_, int y_, int w, int h, const Color &c)
  {
    for (int x = 0; x < width_; x++)
    {
      for (int y = 0; y < height_; y++)
      {
        if (x >= x_ && x < x_ + w && y >= y_ && y < y_ + h)
        {
          pixels[x][y] = c;
        }
      }
    }
  }

  void Image::h_mirror()
  {
    int halfWidth = width_ / 2;
    int height = height_;

    for (int x = 0; x < halfWidth; x++)
    {
      for (int y = 0; y < height; y++)
      {
        int mirroredX = width_ - 1 - x;

        // Store the pixel at (x, y) in a temporary variable
        Color temp = pixels[x][y];

        // Copy the pixel from the mirrored position to (x, y)
        pixels[x][y] = pixels[mirroredX][y];

        // Copy the pixel from the temporary variable to the mirrored position
        pixels[mirroredX][y] = temp;
      }
    }
  }

  void Image::v_mirror()
{
    int width = width_;
    int halfHeight = height_ / 2;
    
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < halfHeight; y++)
        {
            int mirroredY = height_ - 1 - y;
            
            // Store the pixel at (x, y) in a temporary variable
            Color temp = pixels[x][y];
            
            // Copy the pixel from the mirrored position to (x, y)
            pixels[x][y] = pixels[x][mirroredY];
            
            // Copy the pixel from the temporary variable to the mirrored position
            pixels[x][mirroredY] = temp;
        }
    }
}

void Image::add(const Image& img, const Color& neutral, int x, int y)
    {
        if(pixels[x][y] != neutral)
        {
            pixels[x][y] = img.pixels[x][y];
        }
    }


}
