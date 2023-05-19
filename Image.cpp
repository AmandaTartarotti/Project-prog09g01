#include "Image.hpp" // Inclui o arquivo de cabeçalho "Image.hpp"
#include "XPM2.hpp" // Inclui o arquivo de cabeçalho "XPM2.hpp"
#include <cstddef> // Inclui a biblioteca <cstddef> para usar o tipo std::size_t
#include <sstream> // Inclui a biblioteca <sstream> para usar fluxos de string
#include <algorithm> // Inclui a biblioteca <algorithm> para usar funções de algoritmo
#include <fstream> // Inclui a biblioteca <fstream> para operações de arquivo
#include <stdexcept> // Inclui a biblioteca <stdexcept>

using namespace std; // Usa o namespace std

namespace prog // Define um namespace chamado "prog"
{
  // Create image with width w, height h, and all pixels set to color fill.
  Image::Image(int w, int h, const Color &fill)
  {
    width_ = w, height_ = h; // Define width_ como w e height_ como h

    pixels = new Color *[width_]; // Aloca memória para o array de ponteiros de cores com tamanho width_
    for (int i = 0; i < width_; i++) // Loop para cada ponteiro no array de ponteiros
    {
      pixels[i] = new Color[height_]; // Aloca memória para o array de cores com tamanho height_
    }

    for (int i = 0; i < width_; i++) // Loop para cada coluna
    {
      for (int j = 0; j < height_; j++) // Loop para cada linha
      {
        pixels[i][j] = fill; // Atribui a cor de preenchimento à posição (i, j) do array de pixels
      }
    }
  }

  // Implementação do destrutor ~Image()
  Image::~Image()
  {
    for (int i = 0; i < width_; i++) // Loop para cada ponteiro no array de ponteiros
    {
      delete[] pixels[i]; // delete stored pointer
    }

    delete[] pixels; // delete sub array

    pixels = NULL; // Define o ponteiro como NULL para evitar referências inválidas
  }

  //Get image width
  int Image::width() const
  {
    return width_; // Retorna o valor de width_
  }

  //Get image height
  int Image::height() const
  {
    return height_; // Retorna o valor de height_
  }

  //Get mutable reference to the value of pixel (x, y), where 0 <= x < width() and 0 <= y < height()
  Color &Image::at(int x, int y)
  {
    if ((x >= 0 && x < width_) && ( y >= 0 && y < height_)) { // Confere se 0 <= x < width() and 0 <= y < height()
      return pixels[x][y]; // Retorna a referência à cor na posição (x, y) do array de pixels
    }
    else { //Se as condições não forem satisfeitas
      throw std::out_of_range("Invalid pixel coordinates"); // lança uma exceção informando que as coordenadas são inválidas.
    }
  }

  //Get read-only reference to the value of pixel (x, y).
  const Color &Image::at(int x, int y) const
  {

    return pixels[x][y]; // Retorna a referência constante à cor na posição (x, y) do array de pixels
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

void Image::crop(int x, int y, int w, int h){
  
  // Create a new temporary array for the cropped image
  Color **croppedPixels = new Color *[w];

  for (int i = 0; i < w; i++){
    croppedPixels[i] = new Color[h];
  }

  // Copy the pixels within the specified crop area to the temporary array
  for (int i = 0; i < w; i++){
    for (int j = 0; j < h; j++){
      croppedPixels[i][j] = pixels[x + i][y + j];
    }
  }

  // Deallocate the memory of the original image
  for (int i = 0; i < width_; i++){
    delete[] pixels[i];
  }
  delete[] pixels;

  // Update the width and height of the image
  width_ = w;
  height_ = h;

  // Assign the cropped pixels to the image
  pixels = croppedPixels;
}

void Image::rotate_left(){
  
  // Create a new temporary array for the rotated image
  Color **rotatedPixels = new Color *[height_];

  for (int i = 0; i < height_; i++){
    rotatedPixels[i] = new Color[width_];
  }

  // Perform the rotation by copying the pixels in the desired order
  for (int i = 0; i < width_; i++)
  {
    for (int j = 0; j < height_; j++){
      rotatedPixels[height_ - 1 - j][i] = pixels[i][j];
    }
  }

  // Deallocate the memory of the original image
  for (int i = 0; i < width_; i++){
    delete[] pixels[i];
  }

  delete[] pixels;

  // Update the width and height of the image
  int temp = width_;
  width_ = height_;
  height_ = temp;

  // Assign the rotated pixels to the image
  pixels = rotatedPixels;
}

void Image::rotate_right(){

  // Create a new temporary array for the rotated image
  Color **rotatedPixels = new Color *[height_];

  for (int i = 0; i < height_; i++){
    rotatedPixels[i] = new Color[width_];
  }

  // Perform the rotation by copying the pixels in the desired order
  for (int i = 0; i < width_; i++)
  {
    for (int j = 0; j < height_; j++){
      rotatedPixels[j][width_ - 1 - i] = pixels[i][j];
    }
  }

  // Deallocate the memory of the original image
  for (int i = 0; i < width_; i++){
    delete[] pixels[i];
  }

  delete[] pixels;

  // Update the width and height of the image
  int temp = width_;
  width_ = height_;
  height_ = temp;

  // Assign the rotated pixels to the image
  pixels = rotatedPixels;
}

// void Image::median_filter(int ws){
//   // Calculate the offset for the window
//   int offset = ws / 2;

//   // Create a temporary image to store the filtered result
//   Image filteredImage(width_, height_);

//   // Apply the median filter to each pixel
//   for (int y = 0; y < height_; y++){
//     for (int x = 0; x < width_; x++){
//       std::vector<Color> windowColors;

//       // Collect the colors within the window
//       for (int j = -offset; j <= offset; j++){
//         for (int i = -offset; i <= offset; i++){
//           int neighborX = x + i;
//           int neighborY = y + j;

//           // Check if the neighbor pixel is within bounds
//           if (neighborX >= 0 && neighborX < width_ && neighborY >= 0 && neighborY < height_){
//             windowColors.push_back(pixels[neighborX][neighborY]);
//           }
//         }
//       }

//       // Sort the colors within the window
//       std::sort(windowColors.begin(), windowColors.end());

//       // Get the median color
//       Color medianColor = windowColors[windowColors.size() / 2];

//       // Assign the median color to the corresponding pixel in the filtered image
//       filteredImage.pixels[x][y] = medianColor;
//     }
//   }

//   // Copy the filtered image back to the original image
//   *this = filteredImage;
// }

// void Image::xpm2_open(const std::string& filename) {
    
// }

// void Image::xpm2_save(const std::string& filename) {
    
// }

}