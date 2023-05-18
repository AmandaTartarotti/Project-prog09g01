#ifndef __prog_Image_hpp__
#define __prog_Image_hpp__
#include "Color.hpp"
#include <vector>
#include <string>

namespace prog
{
  class Image
  {
  private:
    int width_;
    int height_;
    Color **pixels;

  public:
    Image(int w, int h, const Color &fill = {255, 255, 255});
    ~Image();
    int width() const;
    int height() const;
    Color &at(int x, int y);
    const Color &at(int x, int y) const;
    void invert();
    void to_gray_scale();
    void replace(const Color &a, const Color &b);
    void fill(int x, int y, int w, int h, const Color &c);
    void h_mirror();
    void v_mirror();
    void add(const Image &img, const Color &neutral, int x, int y);
    void crop(int x, int y, int w, int h);
    void rotate_left();
    void rotate_right();
    void median_filter(int ws);
    void xpm2_open(const std::string &filename);
    void xpm2_save(const std::string &filename);
  };
}
#endif
