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
            else if (command == "crop")
            {
                crop();
                continue;
            }
            else if (command == "rotate_left")
            {
                rotate_left();
                continue;
            }
            else if (command == "rotate_right")
            {
                rotate_right();
                continue;
            }
            // else if (command == "median_filter")
            // {
            //     median_filter();
            //     continue;
            // }
            else if (command == "xpm2_open")
            {
                xpm2_open();
                continue;
            }
            // else if (command == "xpm2_save")
            // {
            //     xpm2_save();
            //     continue;
            // }
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
        string filename;
        int r, g, b, x, y;
        input >> filename >> r >> g >> b >> x >> y;

        // Load the image from the PNG file
        Image *newImage = loadFromPNG(filename);

        // Get the dimensions of the new image
        int newWidth = newImage->width();
        int newHeight = newImage->height();

        // Copy pixels from the new image to the current image
        for (int i = 0; i < newHeight; i++)
        {
            for (int j = 0; j < newWidth; j++)
            {
                // Check if the pixel in the new image is not the "neutral" color
                if (newImage->at(j, i) != Color(r, g, b))
                {
                    // Calculate the corresponding position in the current image
                    int currentX = x + j;
                    int currentY = y + i;

                    // Set the pixel in the current image to the corresponding pixel in the new image
                    image->at(currentX, currentY) = newImage->at(j, i);
                }
            }
        }

        // Free the memory allocated
        delete newImage;
    }

    void Script::crop()
    {
        int x, y, w, h;
        input >> x >> y >> w >> h;
        image->crop(x, y, w, h);
    }

    void Script::rotate_left()
    {
        image->rotate_left();
    }

    void Script::rotate_right()
    {
        image->rotate_right();
    }

    // void Script::median_filter()
    // {
    //     int ws;
    //     input >> ws;
    //     image->median_filter(ws);
    // }

    // void Script::xpm2_open()
    // {
    //     std::string filename;
    //     image->xpm2_open(filename);
    // }

    // void Script::xpm2_save()
    // {
    //     std::string filename;
    //     image->xpm2_save(filename);
    // }

}
