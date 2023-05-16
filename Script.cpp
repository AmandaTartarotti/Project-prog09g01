#include <iostream>
#include <fstream>
#include "Script.hpp"
#include "PNG.hpp"
#include "XPM2.hpp"

using namespace std;

namespace prog
{
    // Use to read color values from a script file.
    istream &operator>>(istream &input, Color &c)
    {
        int r, g, b;
        input >> r >> g >> b;
        c.red() = r;
        c.green() = g;
        c.blue() = b;
        return input;
    }

    Script::Script(const string &filename) : image(nullptr), input(filename)
    {
    }
    void Script::clear_image_if_any()
    {
        if (image != nullptr)
        {
            delete image;
            image = nullptr;
        }
    }
    Script::~Script()
    {
        clear_image_if_any();
    }

    void Script::run()
    {
        string command;
        while (input >> command)
        {
            cout << "Executing command '" << command << "' ..." << endl;
            if (command == "open")
            {
                open();
                continue;
            }
            if (command == "blank")
            {
                blank();
                continue;
            }
            // Other commands require an image to be previously loaded.
            if (command == "save")
            {
                save();
                continue;
            }
            else if (command == "invert")
            {
                invert();
                continue;
            }
            else if (command == "to_gray_scale")
            {
                to_gray_scale();
                continue;
            }
            else if (command == "replace")
            {
                replace();
                continue;
            }
            else if (command == "fill")
            {
                fill();
                continue;
            }
            else if (command == "h_mirror")
            {
                h_mirror();
                continue;
            }
            else if (command == "v_mirror")
            {
                v_mirror();
                continue;
            }
            else if (command == "add")
            {
                add();
                continue;
            }

            // TODO ...
        }
    }
    void Script::open()
    {
        // Replace current image (if any) with image read from PNG file.
        clear_image_if_any();
        string filename;
        input >> filename;
        image = loadFromPNG(filename);
    }
    void Script::blank()
    {
        // Replace current image (if any) with blank image.
        clear_image_if_any();
        int w, h;
        Color fill;
        input >> w >> h >> fill;
        image = new Image(w, h, fill);
    }
    void Script::save()
    {
        // Save current image to PNG file.
        string filename;
        input >> filename;
        saveToPNG(filename, image);
    }

    void Script::invert()
    {
        image->invert();
    }

    void Script::to_gray_scale()
    {
        image->to_gray_scale();
    }

    void Script::replace()
    {
        int r1, g1, b1, r2, g2, b2;
        input >> r1 >> g1 >> b1 >> r2 >> g2 >> b2;
        Color a, b;
        a.red() = r1, a.green() = g1, a.blue() = b1;
        b.red() = r2, b.green() = g2, b.blue() = b2;
        image->replace(a, b);
    }

    void Script::fill()
    {
        int x, y, w, h;
        Color c;
        input >> x >> y >> w >> h >> c;
        image->fill(x, y, w, h, c);
    }

    void Script::h_mirror()
    {
        image->h_mirror();
    }

    void Script::v_mirror()
    {
        image->v_mirror();
    }

    void Script::add()
    {
        std::string filename;
        int r, g, b, x, y;
        Image img2 = *loadFromPNG(root_path + "/" + filename);
        input >> filename >> r >> g >> b >> x >> y;
        Color neutral;
        neutral.red() = r, neutral.green() = g, neutral.blue() = b;
        image->add(img2, neutral, x, y);
    }

}
