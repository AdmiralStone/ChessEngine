#include "Game.hpp"

//Rendering Methods
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
                Piece *piece = board.gameBoard[row][col].piece;
                if(piece != dragger.selectedPiece){
                    board.gameBoard[row][col].Draw();
                }
                
            }
        }
    }
    
}

void Game::showPossibleMoves(){
    if(dragger.dragging){
        Piece *selectedPiece = dragger.selectedPiece;

        for(auto move:selectedPiece->getMoveVector()){
            Color sqColor;
            Vector2 boardSquare = move->getFinalSquare();

            int row = boardSquare.x;
            int col = boardSquare.y;

            if(( row + col ) % 2 == 0){
                sqColor = red;
            }else{
                sqColor = lightRed;
            }

            Rectangle square = {(float) col * SQUARE_SIZE , (float)row * SQUARE_SIZE, (float)SQUARE_SIZE, (float)SQUARE_SIZE};
            DrawRectangleRec(square,sqColor);
        }
    }
}
//Methods related to dragger
void Game::updateDragger(Vector2 mousePosition){
    dragger.updateMousePos(mousePosition);
}

void Game::savePiecePosition(Vector2 piecePos){
    dragger.saveInitPiecePos(piecePos);
}

void Game::setDraggedPiece(Piece* selectedPiece){
    dragger.dragPiece(selectedPiece);
}

void Game::unsetDraggedPiece(){
    dragger.unDragPiece();
}

bool Game::isPieceSelected(){
    return dragger.dragging;
}

void Game::hoverPiece(){
    dragger.dragPiece();
}

//Methods related to Board
bool Game::squareHasPiece(Vector2 squarePos){
    return board.gameBoard[squarePos.y][squarePos.x].hasPiece();
}
Piece* Game::getPieceOnSquare(Vector2 squarePos){
    return board.gameBoard[squarePos.y][squarePos.x].piece;
}
void Game::generateMoves(Piece* selectedPiece, int pieceRow, int pieceCol){
    board.calc_moves(selectedPiece,pieceRow,pieceCol);
}



Game::Game(){}
Game::~Game(){}



