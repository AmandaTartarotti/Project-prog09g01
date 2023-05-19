#include "XPM2.hpp"
#include <fstream>

namespace prog {

    Image* loadFromXPM2(const std::string& file) {

        std::ifstream inputFile(file);
        if (!inputFile) {
            //Failed to load file
            return nullptr;
        }

        int widthImg, heightImg, countColorImg;
        inputFile >> widthImg >> heightImg >> countColorImg;

        std::vector<std::string> colorPalette(countColorImg);
        for (int i = 0; i < countColorImg; i++) {
            inputFile >> colorPalette[i];
        }

        std::vector<std::vector<std::string>> pixels(heightImg, std::vector<std::string>(widthImg));
        for (int y = 0; y < heightImg; y++) {
            std::string pixelRow;
            inputFile >> pixelRow;
            if (pixelRow.length() != widthImg) {
                //Invalid XPM data: insufficient pixels in some row
                return nullptr;
            }
            for (int x = 0; x < widthImg; x++) {
                char colorIndex = pixelRow[x];
                if (colorIndex >= '0' && colorIndex < '0' + countColorImg) {
                    pixels[y][x] = colorPalette[colorIndex - '0'];
                } else {
                    //Invalid XPM data: invalid color index at some position
                    return nullptr;
                }
            }
        }

        inputFile.close();

        Image* newImage = new Image(widthImg, heightImg);
        return newImage;
    }

    void saveToXPM2(const std::string& file, const Image* image) {
        
    }
    
}