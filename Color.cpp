#include "Color.hpp"

namespace prog
{

    const Color Color::BLACK(0, 0, 0);
    const Color Color::WHITE(255, 255, 255);
    const Color Color::RED(255, 0, 0);
    const Color Color::GREEN(0, 255, 0);
    const Color Color::BLUE(0, 0, 255);

    Color::Color()
    {
        r = 0;
        g = 0;
        b = 0;
    }
    Color::Color(const Color &other)
    {
        r = other.red();
        g = other.green();
        b = other.blue();
    }
    Color::Color(rgb_value red, rgb_value green, rgb_value blue)
    {
        r = red;
        g = green;
        b = blue;
    }
    rgb_value Color::red() const
    {
        return r;
    }
    rgb_value Color::green() const
    {
        return g;
    }
    rgb_value Color::blue() const
    {
        return b;
    }

    rgb_value &Color::red()
    {
        return r;
    }
    rgb_value &Color::green()
    {
        return g;
    }
    rgb_value &Color::blue()
    {
        return b;
    }

}
