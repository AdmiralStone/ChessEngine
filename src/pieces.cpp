#include "Piece.hpp"
#include <raylib.h>

class Pawn: public Piece{
    public:
        Pawn(Color color){
            PieceType = PAWN;
            name = "pawn";
            this->color = color;
            value = 1.0;
            direction = ColorEq(color,WHITE)?-1:1;

            setTexture();
        }

        void setMoved(){
            moved = true;
        }

        

};

class Knight: public Piece{
    public:
        Knight(Color color){
            PieceType = KNIGHT;
            name = "knight";
            this->color = color;
            value = 3.0;

            setTexture();

        }

};

class Bishop: public Piece{
    public:
        Bishop(Color color){
            PieceType = BISHOP;
            name = "bishop";
            this->color = color;
            value = 3.001;

            setTexture();
        }

};

class Rook: public Piece{
    public:
        Rook(Color color){
            PieceType = ROOK;
            name = "rook";
            this->color = color;
            value = 5.0;

            setTexture();
        }

};

class Queen: public Piece{
    public:
        Queen(Color color){
            PieceType = QUEEN;
            name = "queen";
            this->color = color;
            value = 9.0;

            setTexture();
        }
};

class King: public Piece{
    public:
        King(Color color){
            PieceType = KING;
            name = "king";
            this->color = color;
            value = INT_MAX;

            setTexture();
        }

};

