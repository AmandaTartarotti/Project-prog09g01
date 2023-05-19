#include <iostream> // Inclui a biblioteca de entrada/saída padrão. 
#include <algorithm> // Inclui a biblioteca de algoritmos padrão.
#include <fstream> // Inclui a biblioteca de manipulação de arquivos.
#include "Script.hpp" // Inclui o cabeçalho do arquivo "Script.hpp".
#include "PNG.hpp" // Inclui o cabeçalho do arquivo "PNG.hpp".
#include "XPM2.hpp" // Inclui o cabeçalho do arquivo "XPM2.hpp".

using namespace std; // Usa o namespace std

namespace prog
{
    // Sobrecarga do operador de extração (>>) para ler valores de cor de um arquivo de script.
    istream &operator>>(istream &input, Color &c)
    {
        int r, g, b;
        input >> r >> g >> b; // Lê os valores de vermelho, verde e azul da cor a partir do fluxo de entrada.
        c.red() = r; // Atribui o valor de vermelho à cor.
        c.green() = g; // Atribui o valor de verde à cor.
        c.blue() = b; // Atribui o valor de azul à cor.
        return input; // Retorna o fluxo de entrada para permitir encadeamento.
    }


    /* Construtor da classe Script que recebe o nome do arquivo como parâmetro e
    inicializa o ponteiro da imagem com nullptr e associa o fluxo de entrada ao arquivo.*/
    Script::Script(const string &filename) : image(nullptr), input(filename) { }

    
    // Método da classe Script responsável por liberar a memória ocupada pela imagem, se existir.
    void Script::clear_image_if_any()
    {
        // Verifica se o ponteiro da imagem não é nulo.
        if (image != nullptr)
        {
            // Libera a memória ocupada pela imagem.
            delete image;
            // Define o ponteiro da imagem como nulo.
            image = nullptr;
        }
    }


    // Destrutor da classe Script responsável por liberar a memória ocupada pela imagem, se existir.
    Script::~Script()
    {
        // Chama o método clear_image_if_any() para liberar a memória da imagem.
        clear_image_if_any();
    }

    // Comandos que podem ser executados nos testes.
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
            // Outros comandos requerem que uma imagem seja carregada previamente.
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
            
            else if (command == "median_filter")
            {
                 median_filter();
                 continue;
            }

            else if (command == "xpm2_open")
            {
                 xpm2_open();
                 continue;
            }

            else if (command == "xpm2_save"){
                 xpm2_save();
                 continue;
            }
        }
    }


    void Script::open()
    {
        // Substitui a imagem atual, se houver, pela imagem lida do arquivo PNG.
        clear_image_if_any();
        string filename;
        input >> filename;
        image = loadFromPNG(filename);
    }


    void Script::blank()
    {
        // Substitui a imagem atual, se houver, por uma imagem em branco.
        clear_image_if_any();
        int w, h;
        Color fill;
        input >> w >> h >> fill;
        image = new Image(w, h, fill);
    }


    void Script::save()
    {
        // Salva a imagem atual no arquivo PNG.
        string filename;
        input >> filename;
        saveToPNG(filename, image);
    }


    void Script::invert()
    {
        //Chama a função que inverte as cores dos pixels da imagem atual.
        image->invert();
    }


    void Script::to_gray_scale()
    {
        //Chama a função que converte as cores dos pixels da imagem atual para a escala de cinza.
        image->to_gray_scale();
    }


    void Script::replace()
    {
        //Recebe os valores de entrada e chama a função que substitui cada ocorrência da cor 'a' pela cor 'b'.
        int r1, g1, b1, r2, g2, b2;
        input >> r1 >> g1 >> b1 >> r2 >> g2 >> b2;
        Color a, b;
        a.red() = r1, a.green() = g1, a.blue() = b1;
        b.red() = r2, b.green() = g2, b.blue() = b2;
        image->replace(a, b);
    }


    void Script::fill()
    {
        //Recebe os valores de entrada e chama a função que preenche uma região retangular com a cor especificada.
        int x, y, w, h;
        Color c;
        input >> x >> y >> w >> h >> c;
        image->fill(x, y, w, h, c);
    }


    void Script::h_mirror()
    {
        // Chama a função que realiza uma reflexão horizontal da imagem.
        image->h_mirror();
    }


    void Script::v_mirror()
    {
        // Chama a função que realiza uma reflexão vertical da imagem.
        image->v_mirror();
    }

    //Adiciona os pixels de uma outra imagem à imagem atual.
    void Script::add()
    {
        // Variáveis locais para armazenar os valores de entrada
        string filename;
        int r, g, b, x, y;
        input >> filename >> r >> g >> b >> x >> y;

        // Carrega a imagem do arquivo PNG especificado
        Image *newImage = loadFromPNG(filename);

        // Obtém as dimensões da nova imagem
        int newWidth = newImage->width();
        int newHeight = newImage->height();

        // Copia os pixels da nova imagem para a imagem atual
        for (int i = 0; i < newHeight; i++)
        {
            for (int j = 0; j < newWidth; j++)
            {
                // Verifica se o pixel na nova imagem não é da cor "neutra"
                if (newImage->at(j, i) != Color(r, g, b))
                {
                    // Calcula a posição correspondente na imagem atual
                    int currentX = x + j;
                    int currentY = y + i;

                    // Define o pixel na imagem atual como o pixel correspondente na nova imagem
                    image->at(currentX, currentY) = newImage->at(j, i);
                }
            }
        }

        // Libera a memória alocada para a nova imagem
        delete newImage;
    }


    void Script::crop()
    {
        //Recebe os valores de entrada e chama a função que Recorta a imagem atual para uma região retangular especificada por (x, y, w, h).
        int x, y, w, h;
        input >> x >> y >> w >> h;
        image->crop(x, y, w, h);
    }


    void Script::rotate_left()
    {
        //Chama a função que rotaciona a imagem atual em 90 graus para a esquerda.
        image->rotate_left();
    }


    void Script::rotate_right()
    {
        //Chama a função que rotaciona a imagem atual em 90 graus para a direita.
        image->rotate_right();
    }

    //Funcionalidades avançadas.

    //Aplica um filtro de média com uma ws mínima de tamanha 3.
    void Script::median_filter() {
        int ws;
        input >> ws; // Lê o tamanho da janela de entrada

        int w = image->width();
        int h = image->height();
        Image* newImage = new Image(w, h); // Cria uma nova imagem para armazenar o resultado filtrado

        // Percorre cada pixel na imagem
        for (int y = 0; y < h; y++) {
            for (int x = 0; x < w; x++) {
                std::vector<int> reds;
                std::vector<int> greens;
                std::vector<int> blues;

                // Percorre os pixels vizinhos dentro da janela
                for (int ny = std::max(0, y - ws / 2); ny <= std::min(h - 1, y + ws / 2); ny++) {
                    for (int nx = std::max(0, x - ws / 2); nx <= std::min(w - 1, x + ws / 2); nx++) {
                        Color& c = image->at(nx, ny);
                        reds.push_back(c.red());
                        greens.push_back(c.green());
                        blues.push_back(c.blue());
                    }
                }

                // Ordena os canais de cor separadamente
                std::sort(reds.begin(), reds.end());
                std::sort(greens.begin(), greens.end());
                std::sort(blues.begin(), blues.end());

                // Encontra os valores medianos das cores para cada canal
                int size = reds.size();
                int medianRed, medianGreen, medianBlue;

                if (size % 2 != 0) {
                    medianRed = reds[size / 2];
                    medianGreen = greens[size / 2];
                    medianBlue = blues[size / 2];
                } else {
                    medianRed = (reds[size / 2] + reds[size / 2 - 1]) / 2;
                    medianGreen = (greens[size / 2] + greens[size / 2 - 1]) / 2;
                    medianBlue = (blues[size / 2] + blues[size / 2 - 1]) / 2;
                }

                // Define os valores de cor medianos para o pixel atual na nova imagem
                Color& newPixel = newImage->at(x, y);
                newPixel.red() = medianRed;
                newPixel.green() = medianGreen;
                newPixel.blue() = medianBlue;
            }
        }

        // Limpeza
        delete image; // Libera a memória alocada para a imagem original
        image = newImage; // Atualiza a referência para a nova imagem filtrada
    }



    void Script::xpm2_open()
    {
        std::string filename;
        image->xpm2_open(filename);
    }
    
    
    void Script::xpm2_save()
    {
        std::string filename;
        image->xpm2_save(filename);
    }

}