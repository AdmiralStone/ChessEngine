#pragma once

#include <string>
#include <raylib.h>
#include "Colors.hpp"


class Piece
{
protected:
    /* data */
    
    Color color;
    float value;
    int direction;
    

    void setTexture();

public:
    std::string name;
    Texture2D texture;

    Piece();
    ~Piece();
};

