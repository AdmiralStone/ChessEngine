#include <iostream>
#include <stdio.h>
#include <raylib.h>
#include "Globals.hpp"
#include "Setup.hpp"

int main(){
    InitWindow(WIN_WIDTH , WIN_HEIGHT, "Chess");

    SetTargetFPS(TARGET_FPS);

    Setup gameSetup = Setup();

    while(!WindowShouldClose()){
        BeginDrawing();

            gameSetup.DrawBackground();

        EndDrawing();
    }

    CloseWindow();

    return 0;

}