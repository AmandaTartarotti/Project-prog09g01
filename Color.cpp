#include "Color.hpp"  // Inclui o arquivo de cabeçalho "Color.hpp"

namespace prog // Define um namespace chamado "prog"
{
    // Define as constantes estáticas e seus respectivos valores
    const Color Color::BLACK(0, 0, 0); // Define uma constante estática Color chamada BLACK com os valores (0, 0, 0)
    const Color Color::WHITE(255, 255, 255); // Define uma constante estática Color chamada WHITE com os valores (255, 255, 255)
    const Color Color::RED(255, 0, 0); // Define uma constante estática Color chamada RED com os valores (255, 0, 0)
    const Color Color::GREEN(0, 255, 0); // Define uma constante estática Color chamada GREEN com os valores (0, 255, 0)
    const Color Color::BLUE(0, 0, 255); // Define uma constante estática Color chamada BLUE com os valores (0, 0, 255)

    // Default constructor. By default, the color should correspond to black, i.e., (0, 0, 0).
    Color::Color()
    {
        r = 0; // Define o valor de r como 0
        g = 0; // Define o valor de g como 0
        b = 0; // Define o valor de b como 0
    }

    // Implementação do construtor de cópia Color(const Color &other)
    Color::Color(const Color &other)
    {
        r = other.red(); // Define o valor de r como o valor de red de 'other'
        g = other.green(); // Define o valor de g como o valor de green de 'other'
        b = other.blue(); // Define o valor de b como o valor de blue de 'other'
    }

    // Implementação do construtor using supplied (r, g, b) values
    Color::Color(rgb_value red, rgb_value green, rgb_value blue)
    {
        r = red; // Define o valor de r como 'red'
        g = green; // Define o valor de g como 'green'  
        b = blue; // Define o valor de b como 'blue'
    }

    //Get values for individual RGB color channels
    rgb_value Color::red() const // Implementação do getter red()
    {
        return r; // Retorna o valor de r
    }
    rgb_value Color::green() const // Implementação do getter green()
    {
        return g; // Retorna o valor de g
    }
    rgb_value Color::blue() const // Implementação do getter blue()
    {
        return b; // Retorna o valor de b
    }

    // Get (mutable) references for individual RGB color channels
    rgb_value &Color::red() // Implementação do setter red()
    {
        return r; // Retorna a referência de r
    }
    rgb_value &Color::green() // Implementação do setter green()
    {
        return g; // Retorna a referência de g
    }
    rgb_value &Color::blue() // Implementação do setter blue()
    {
        return b; // Retorna a referência de b
    }

    void Color::invert() // Implementação da função invert()
    {
        r = 255 - r; // Inverte o valor de r
        g = 255 - g; // Inverte o valor de g
        b = 255 - b; // Inverte o valor de b
    }


    // Transforms each individual pixel (r, g, b) to (v, v, v) where v = (r + g + b)/3.
    void Color::to_gray_scale()
    {
        int v = (r + g + b) / 3; // Calcula a média dos valores de r, g e b
        r = v; // Define o valor de r como a média
        g = v; // Define o valor de g como a média
        b = v; // Define o valor de b como a média
    }

    // Implementação do operador de atribuição =
    Color &Color::operator=(const Color &c) 
    {
        r = c.red(); // Atribui o valor de red de 'c' a r
        g = c.green(); // Atribui o valor de green de 'c' a g
        b = c.blue();  // Atribui o valor de blue de 'c' a b
        return *this; // Retorna o objeto atual
    }

    // Implementação do operador de igualdade ==
    bool Color::operator==(const Color &c) const // Implementação do operador de igualdade ==
    {

        // Verifica se os valores de r, g e b são iguais aos valores correspondentes de 'c'
        if (r == c.r && g == c.g && b == c.b)
        {
            return true; // Retorna true se forem iguais
        }
        else
        {
            return false; // Retorna false se forem diferentes
        }
    }

    // Implementação do operador de desigualdade !=
    bool Color::operator!=(const Color &c) const 
    {
        
        // Verifica se os valores de r, g e b são iguais aos valores correspondentes de 'c'
        if (r == c.r && g == c.g && b == c.b)
        {
            return false; // Retorna true se forem iguais
        }
        else
        {
            return true; // Retorna false se forem diferentes
        }
    }

}
