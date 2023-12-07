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

            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                Vector2 currentMousePos = GetMousePosition();

                game.updateDragger(currentMousePos);

                int selectedCol = currentMousePos.x/SQUARE_SIZE;
                int selectedRow  = currentMousePos.y/SQUARE_SIZE;

                Vector2 squarePos = {(float)selectedCol,(float)selectedRow};

                if(game.squareHasPiece(squarePos) && game.checkIfPlayerPiece(squarePos)){
                    Piece *piece = game.getPieceOnSquare(squarePos);

                    game.generateMoves(piece,squarePos.y,squarePos.x);

                    game.savePiecePosition(squarePos);

                    game.setDraggedPiece(piece);

                }
            }else if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && game.isPieceSelected()){
                Vector2 currentMousePos = GetMousePosition();
                game.updateDragger(currentMousePos);

                int selectedCol = currentMousePos.x/SQUARE_SIZE;
                int selectedRow  = currentMousePos.y/SQUARE_SIZE;

                Vector2 finalPos = {(float)selectedCol,(float)selectedRow};
                Move *newMove = game.createNewMove(finalPos);

                if(game.validateMove(newMove)){
                    game.movePiece(newMove);
                }

                game.unsetDraggedPiece();
            }else if(game.isPieceSelected()){
                Vector2 currentMousePos = GetMousePosition();
                game.updateDragger(currentMousePos);

                game.showPossibleMoves();

            }

            game.DrawPieces();

            if(game.isPieceSelected()){
                game.hoverPiece();
            }

            

        EndDrawing();
    }

    CloseWindow();

    return 0;

}