#pragma once

#include "Globals.hpp"
#include "Colors.hpp"
#include "raylib.h"
#include "Square.hpp"
#include "Move.hpp"

#include <vector>

class Board
{
private:

public:
    Board();
    ~Board();

    std::vector<std::vector<Square>> gameBoard;

    void createBoard();
    void initializePieces(Color pieceColor);
    
    void calc_moves(Piece* , int, int);// Calculate all the valid moves of a specific piece at a specific position
    void Knight_Moves(Piece*,int,int); // Generate POssible Moves for Knight
    void Pawn_Moves(Piece*,int,int); // Generate POssible Moves for Pawn
    void Straight_line_Moves(Piece*,int,int,std::vector<std::vector<int>>); // Generate Possible moves for Rook,Bishop and Queen
    void King_Moves(Piece*,int,int);

    void ProcessMove(Move*);
    bool ValidateMove(Piece*, Move*);
};



