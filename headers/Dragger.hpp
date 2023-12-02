#pragma once

#include "Globals.hpp"
#include "Colors.hpp"
#include "raylib.h"
#include "Piece.hpp"

class Dragger
{
public:
    Dragger(/* args */);
    ~Dragger();

    float mouseX = 0;
    float mouseY = 0;
    int initPieceRow = 0;
    int initPieceCol = 0;
    Piece* selectedPiece;
    bool dragging = false;
    

    void updateMousePos(Vector2);
    void saveInitPiecePos(Vector2);
    void dragPiece(Piece*);
    void unDragPiece();
    void dragPiece();

};


