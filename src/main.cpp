#include <iostream>
#include <stdio.h>
#include "Globals.hpp"
#include "Game.hpp"
#include "raylib.h"

int main(){
    InitWindow(WIN_WIDTH , WIN_HEIGHT, "Chess");

    SetTargetFPS(TARGET_FPS);

    Game game = Game();

    while(!WindowShouldClose()){
        BeginDrawing();

            game.DrawBackground();

            game.DrawPieces();

        EndDrawing();
    }

    CloseWindow();

    return 0;

}