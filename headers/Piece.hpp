#pragma once

#include <string>
#include <raylib.h>
#include "Colors.hpp"
#include "Globals.hpp"
#include "Move.hpp"


class Piece
{
protected:
    /* data */
    PIECE_TYPE PieceType;
    Color color;
    float value;
    int direction;
    std::vector<Move*> validMoves;
    bool moved = false;

public:
    std::string name;
    Texture2D texture;

    void setTexture(int size=80);
    PIECE_TYPE getPieceType();
    Color getPieceColor();
    void addMoves(Move*);
    std::vector<Move*> getMoveVector();
    
    bool checkIfMoved(); // Method used only for PAWN child to see if the pawn is at starting position
    int getPieceDirection();
    void setMoved();

    Piece();
    ~Piece();
};

