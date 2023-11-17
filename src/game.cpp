#include "Game.hpp"
#include <stdio.h>

void Game::DrawBackground(){
    for(int row = 0; row<ROWS;row++){
        for(int col = 0; col<COLS;col++){
            Color sqColor;

            if((row+col) % 2 == 0){
                sqColor = lightGreen;
            }else{
                sqColor = darkGreen;
            }

            Rectangle square = {(float) col * SQUARE_SIZE , (float)row * SQUARE_SIZE, (float)SQUARE_SIZE, (float)SQUARE_SIZE};
            DrawRectangleRec(square,sqColor);

        }
    }
}

void Game::DrawPieces(){
    for(int row = 0; row<ROWS; row++){
        for(int col = 0; col<COLS;col++){
            if(board.gameBoard[row][col].hasPiece()){
                board.gameBoard[row][col].Draw();
            }
        }
    }
    
}

Game::Game(){}
Game::~Game(){}



