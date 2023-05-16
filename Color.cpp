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

    void Color::invert()
    {
        r = 255 - r, g = 255 - g, b = 255 - b;
    }

    void Color::to_gray_scale()
    {
        int v = (r + g + b) / 3;
        r = v, g = v, b = v;
        // r=r*0.299083;
        // g=g*0.586611;
        // b=b*0.114076;
    }

    Color &Color::operator=(const Color &c)
    {
        r = c.red();
        g = c.green();
        b = c.blue();
        return *this;
    }

    bool Color::operator==(const Color &c) const
    {

        if (r == c.r && g == c.g && b == c.b)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool Color::operator!=(const Color &c) const
    {

        if (r == c.r && g == c.g && b == c.b)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

}
