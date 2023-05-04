/*

A Color object represents an RGB color, that is, a color defined by 3 integer values which are the values for the red, green, and 
blue color channels for the color at stake. Each of these values takes one byte and can take values ranging from 0 to 255, 
as defined by type rgb_value in Color.hpp.

*/

#include "Color.hpp"

namespace prog {

    Color::Color()  { 
        r_(0);
        g_(0);
        b_(0);
    }

    Color::Color(const Color& other) : r_(other.r_), g_(other.g_), b_(other.b_) { } 
    
    Color::Color(rgb_value red, rgb_value green, rgb_value blue): r_(red), g_(green), b_(blue) { }

    rgb_value Color::red() const {
        return r_;
    }
    rgb_value Color::green() const {
        return g_;
    }
    rgb_value Color::blue() const {
        return b_;
    }

    rgb_value& Color::red()  {
        return r_;
    }
    rgb_value& Color::green()  {
      return g_;
    }
    rgb_value& Color::blue()  {
      return b_;
    }
}
