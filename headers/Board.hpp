#pragma once

#include "Square.hpp"
#include "Globals.hpp"
#include "Colors.hpp"
#include "raylib.h"


#include <vector>

class Board
{
private:

public:
    Board(/* args */);
    ~Board();

    std::vector<std::vector<Square>> gameBoard;

    void createBoard();
    void initializePieces(Color pieceColor);

};



