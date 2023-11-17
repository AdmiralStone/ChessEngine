#pragma once

#include "Piece.hpp"
#include "Globals.hpp"
#include "string"
#include <iostream>


class Square
{
private:
    /* data */
    unsigned int square_row_pos;
    unsigned int square_col_pos;
    

public:
    Square(int row, int col);
    ~Square();
    
    Piece* piece;

    void setPiece(Piece* newPiece);
    bool hasPiece();

    void Draw();
};

