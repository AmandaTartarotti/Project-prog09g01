#ifndef __prog_Script_hpp__
#define __prog_Script_hpp__

#include <string>
#include <fstream>
#include "Image.hpp"

namespace prog
{
  class Script
  {
  public:
    // Funções públicas
    Script(const std::string &filename);
    ~Script();
    void run();

  private:
    // Imagem atual
    Image *image;
    // Fluxo de entrada para leitura de comandos de script
    std::ifstream input;
    std::string root_path;

  private:
    // Funções privadas
    void clear_image_if_any();
    void open();
    void blank();
    void save();
    void invert();
    void to_gray_scale();
    void replace();
    void fill();
    void h_mirror();
    void v_mirror();
    void add();
    void crop();
    void rotate_left();
    void rotate_right();
    void median_filter();
    void xpm2_open();
    void xpm2_save();
  };
}
#endif
