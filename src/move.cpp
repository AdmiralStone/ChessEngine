#include "Move.hpp"

Move::Move(Vector2 originalSquare,Vector2 possibleSquare)
{
    initialSqarePos = originalSquare;
    finalSquarePos = possibleSquare;
}

Move::~Move()
{
}

Vector2 Move::getFinalSquare(){
    return finalSquarePos;
}

Vector2 Move::getInitialSquare(){
    return initialSqarePos;
}