#pragma once

#include "Board.hpp"
#include <iostream>
#include <raylib.h>
#include "Globals.hpp"
#include "Colors.hpp"

class Game{
    private:
        Board board = Board();
    public:
        Game();
        ~Game();

        void DrawBackground();
        void DrawPieces();

};