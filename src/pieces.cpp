#include "Piece.hpp"
#include <raylib.h>

class Pawn: public Piece{
    public:
        Pawn(Color color){
            name = "pawn";
            this->color = color;
            value = 1.0;
            direction = ColorEq(color,WHITE)?-1:1;

            setTexture();
        }
};

class Knight: public Piece{
    public:
        Knight(Color color){
            name = "knight";
            this->color = color;
            value = 3.0;

            setTexture();
        }
};

class Bishop: public Piece{
    public:
        Bishop(Color color){
            name = "bishop";
            this->color = color;
            value = 3.001;

            setTexture();
        }
};

class Rook: public Piece{
    public:
        Rook(Color color){
            name = "rook";
            this->color = color;
            value = 5.0;

            setTexture();
        }
};

class Queen: public Piece{
    public:
        Queen(Color color){
            name = "queen";
            this->color = color;
            value = 9.0;

            setTexture();
        }
};

class King: public Piece{
    public:
        King(Color color){
            name = "king";
            this->color = color;
            value = INT_MAX;

            setTexture();
        }
};

