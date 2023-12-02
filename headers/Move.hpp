#pragma once


#include "raylib.h"

class Move
{
protected:
    /* data */
   Vector2 initialSqarePos;
   Vector2 finalSquarePos;

public:
   Move(Vector2, Vector2);
   ~Move();

   Vector2 getFinalSquare();
};


