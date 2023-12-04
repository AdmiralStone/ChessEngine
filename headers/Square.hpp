#pragma once

#include "Piece.hpp"
#include "Globals.hpp"
#include "string"
#include <iostream>
#include "Colors.hpp"


class Square
{
private:
    /* data */
    // unsigned int square_row_pos;
    // unsigned int square_col_pos;
    

public:
    //Change Later make private
    unsigned int square_row_pos;
    unsigned int square_col_pos;

    Square(int row, int col);
    ~Square();
    
    Piece* piece;

    void setPiece(Piece*);
    bool hasPiece();
    Piece* getPiece();
    void deletePiece();

    static bool inRange(int,int); // Tells us if the passed row/col is within the range of the board
    bool empty_or_rival(Color); // Checks if square is empty or has any rival piece
    bool hasRivalPiece(Color); //Return True if square has a rival piece
    bool hasTeamPiece(Color); //Check if the square has the same color piece
    bool isEmpty();
    void Draw();



};

