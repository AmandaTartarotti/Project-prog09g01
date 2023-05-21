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
  // Crie uma imagem com largura w, altura h e todos os pixels definidos para preenchimento de cor.
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


  //Obter largura da imagem
  int Image::width() const
  {
    return width_; // Retorna o valor de width_
  }


  //Obter altura da imagem
  int Image::height() const
  {
    return height_; // Retorna o valor de height_
  }


  //Obtém referência para o valor do pixel (x, y), onde 0 <= x < width() e 0 <= y < height()
  Color &Image::at(int x, int y)
  {
    if ((x >= 0 && x < width_) && ( y >= 0 && y < height_)) { // Confere se 0 <= x < width() and 0 <= y < height()
      return pixels[x][y]; // Retorna a referência à cor na posição (x, y) do array de pixels
    }

    else { //Se as condições não forem satisfeitas
      throw std::out_of_range("Invalid pixel coordinates"); // lança uma exceção informando que as coordenadas são inválidas.
    }
  }


  //Obter referência somente leitura para o valor do pixel (x, y).
  const Color &Image::at(int x, int y) const
  {
    return pixels[x][y]; // Retorna a referência constante à cor na posição (x, y) do array de pixels
  }


  // Transforma cada pixel individual (r, g, b) para (255-r, 255-g, 255-b)
  void Image::invert()
  {
    for (int i = 0; i < width_; i++) // Percorre cada coluna da imagem
    {
      for (int j = 0; j < height_; j++) // Percorre cada linha da imagem
      {
        pixels[i][j].invert(); // Inverte as cores do pixel atual
      }
    }
  }

  // Transforma cada pixel individual (r, g, b) para a escala de cinza
  void Image::to_gray_scale()
  {
    for (int i = 0; i < width_; i++) // Percorre cada coluna da imagem
    {
      for (int j = 0; j < height_; j++) // Percorre cada linha da imagem
      {
        pixels[i][j].to_gray_scale(); // Converte o pixel atual para escala de cinza
      }
    }
  }

  // Substitui cada ocorrência da cor 'a' pela cor 'b'
  void Image::replace(const Color &a, const Color &b)
  {
    for (int i = 0; i < width_; i++) // Percorre cada coluna da imagem
    {
      for (int j = 0; j < height_; j++) // Percorre cada linha da imagem
      {
        if (pixels[i][j] == a) // Verifica se o pixel atual é igual à cor 'a'
        {
          pixels[i][j] = b; // Substitui o pixel atual pela cor 'b'
        }
      }
    }
  }

  // Preenche uma região retangular com a cor especificada
  void Image::fill(int x_, int y_, int w, int h, const Color &c)
  {
    for (int x = 0; x < width_; x++) // Percorre cada coluna da imagem
    {
      for (int y = 0; y < height_; y++) // Percorre cada linha da imagem
      {
        if (x >= x_ && x < x_ + w && y >= y_ && y < y_ + h) // Verifica se o pixel atual está dentro da região retangular especificada
        {
          pixels[x][y] = c; // Preenche o pixel atual com a cor 'c'
        }
      }
    }
  }


  // Realiza uma reflexão horizontal da imagem
  void Image::h_mirror()
  {
    int halfWidth = width_ / 2; // Obtém a metade da largura da imagem
    int height = height_; // Obtém a altura da imagem

    for (int x = 0; x < halfWidth; x++) // Percorre até a metade da largura da imagem
    {
      for (int y = 0; y < height; y++) // Percorre toda a altura da imagem
      {
        int mirroredX = width_ - 1 - x; // Calcula a posição refletida horizontalmente
        Color temp = pixels[x][y]; // Armazena temporariamente o valor do pixel original
        pixels[x][y] = pixels[mirroredX][y]; // Substitui o pixel original pelo pixel refletido
        pixels[mirroredX][y] = temp; // Substitui o pixel refletido pelo valor temporário
      }
    }
  }


  // Realiza uma reflexão vertical da imagem
  void Image::v_mirror()
  {
    int width = width_; // Obtém a largura da imagem
    int halfHeight = height_ / 2; // Obtém a metade da altura da imagem

    for (int x = 0; x < width; x++) // Percorre toda a largura da imagem
    {
      for (int y = 0; y < halfHeight; y++) // Percorre até a metade da altura da imagem
      {
        int mirroredY = height_ - 1 - y; // Calcula a posição refletida verticalmente
        Color temp = pixels[x][y]; // Armazena temporariamente o valor do pixel original
        pixels[x][y] = pixels[x][mirroredY]; // Substitui o pixel original pelo pixel refletido
        pixels[x][mirroredY] = temp; // Substitui o pixel refletido pelo valor temporário
      }
    }
  }


  //Implementada no ficheiro Script.cpp.
  void Image::add(const Image& img2, const Color& neutral, int x, int y) {  }


  // Recorta a imagem atual para uma região retangular especificada por (x, y, w, h)
  void Image::crop(int x, int y, int w, int h)
  {
    // Cria uma nova matriz de pixels para a imagem recortada
    Color **croppedPixels = new Color *[w];

    // Aloca memória para a matriz de pixels da imagem recortada
    for (int i = 0; i < w; i++)
    {
      croppedPixels[i] = new Color[h];
    }

    // Copia os pixels da região retangular especificada para a matriz de pixels recortada
    for (int i = 0; i < w; i++)
    {
      for (int j = 0; j < h; j++)
      {
        croppedPixels[i][j] = pixels[x + i][y + j];
      }
    }

    // Libera a memória ocupada pela matriz de pixels original
    for (int i = 0; i < width_; i++)
    {
      delete[] pixels[i];
    }
    delete[] pixels;

    // Atualiza a largura e altura da imagem para as dimensões do recorte
    width_ = w;
    height_ = h;

    // Atualiza a matriz de pixels para a matriz recortada
    pixels = croppedPixels;
  }


  // Rotaciona a imagem atual em 90 graus para a esquerda
  void Image::rotate_left()
  {
    // Cria uma nova matriz de pixels para a imagem rotacionada
    Color **rotatedPixels = new Color *[height_];

    // Aloca memória para a matriz de pixels da imagem rotacionada
    for (int i = 0; i < height_; i++)
    {
      rotatedPixels[i] = new Color[width_];
    }

    // Copia os pixels da imagem original para a matriz de pixels rotacionada
    for (int i = 0; i < width_; i++)
    {
      for (int j = 0; j < height_; j++)
      {
        rotatedPixels[j][width_ - i - 1] = pixels[i][j];
      }
    }

    // Libera a memória ocupada pela matriz de pixels original
    for (int i = 0; i < width_; i++)
    {
      delete[] pixels[i];
    }
    delete[] pixels;

    // Atualiza a largura e altura da imagem trocando os valores
    int temp = width_;
    width_ = height_;
    height_ = temp;

    // Atualiza a matriz de pixels para a matriz rotacionada
    pixels = rotatedPixels;
  }


  // Rotaciona a imagem atual em 90 graus para a direita
  void Image::rotate_right()
  {
    // Cria uma nova matriz de pixels para a imagem rotacionada
    Color **rotatedPixels = new Color *[height_];

    // Aloca memória para a matriz de pixels da imagem rotacionada
    for (int i = 0; i < height_; i++)
    {
      rotatedPixels[i] = new Color[width_];
    }

    // Copia os pixels da imagem original para a matriz de pixels rotacionada
    for (int i = 0; i < width_; i++)
    {
      for (int j = 0; j < height_; j++)
      {
        rotatedPixels[height_ - j - 1][i] = pixels[i][j];
      }
    }

    // Libera a memória ocupada pela matriz de pixels original
    for (int i = 0; i < width_; i++)
    {
      delete[] pixels[i];
    }
    delete[] pixels;

    // Atualiza a largura e altura da imagem trocando os valores
    int temp = width_;
    width_ = height_;
    height_ = temp;

    // Atualiza a matriz de pixels para a matriz rotacionada
    pixels = rotatedPixels;
  }

  //Implementada no ficheiro Script.cpp.
  void Image::median_filter(int ws) { }


  void Image::xpm2_open(const std::string& filename) { }

  
  void Image::xpm2_save(const std::string& filename) { }

}