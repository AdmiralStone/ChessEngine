#include <iostream>
#include <raylib.h>
#include "Globals.hpp"
#include "Colors.hpp"
#include "Setup.hpp"

void Setup::DrawBackground(){
    for(int row = 0; row<ROWS;row++){
        for(int col = 0; col<COLS;col++){
            Color sqColor;

            if((row+col) % 2 == 0){
                sqColor = lightGreen;
            }else{
                sqColor = darkGreen;
            }

            Rectangle block = {(float) col * BLOCK_SIZE , (float)row * BLOCK_SIZE, (float)BLOCK_SIZE, (float)BLOCK_SIZE};
            DrawRectangleRec(block,sqColor);
        }
    }
}



