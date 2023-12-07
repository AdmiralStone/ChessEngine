#pragma once

#include "Board.hpp"
#include <raylib.h>
#include "Globals.hpp"
#include "Colors.hpp"
#include "Dragger.hpp"
#include "Move.hpp"

class Game{
    private:
        Board board = Board();
        Dragger dragger = Dragger();
        int currentPlayer = PLAYER_ONE;

    public:
        Game();
        ~Game();

        void DrawBackground();
        void DrawPieces();
        void updateDragger(Vector2);
        bool squareHasPiece(Vector2);
        Piece* getPieceOnSquare(Vector2);
        void generateMoves(Piece*,int,int); // Call the calc_moves method on the board class
        void savePiecePosition(Vector2);
        void setDraggedPiece(Piece*);
        void unsetDraggedPiece();
        bool isPieceSelected();
        void hoverPiece();
        void showPossibleMoves();
        Move* createNewMove(Vector2);
        bool validateMove(Move*);
        void movePiece(Move*);
        void switchPlayer(); //Switch player after move
        bool checkIfPlayerPiece(Vector2);// Check if pieceColor matches current Player color
        


};