#include "Board.hpp"
#include "pieces.cpp"

void Board::createBoard(){
    for(int row = 0; row < ROWS; row++){
        std::vector<Square> squareRow;
        for(int col = 0; col < COLS; col++){
            Square BoardSquare = Square(row,col);
            squareRow.push_back(BoardSquare);

        }
        gameBoard.push_back(squareRow);
    }
}

void Board::initializePieces(Color pieceColor){
    int pieceRow;
    int pawnRow;
    //Initialize Pawns
    if(ColorEq(pieceColor,WHITE)){
        pieceRow = 7;
        pawnRow = 6;
    }else{
        pieceRow = 0;
        pawnRow = 1;
    }

    for(int i = 0;i<COLS;i++){
        gameBoard[pawnRow][i].setPiece(new Pawn(pieceColor));
    }

    //Knight
    gameBoard[pieceRow][1].setPiece(new Knight(pieceColor));
    gameBoard[pieceRow][6].setPiece(new Knight(pieceColor));

    //bishops
    gameBoard[pieceRow][2].setPiece(new Bishop(pieceColor));
    gameBoard[pieceRow][5].setPiece(new Bishop(pieceColor));

    //rooks
    gameBoard[pieceRow][0].setPiece(new Rook(pieceColor));
    gameBoard[pieceRow][7].setPiece(new Rook(pieceColor));

    //queen
    gameBoard[pieceRow][3].setPiece(new Queen(pieceColor));

    //King
    gameBoard[pieceRow][4].setPiece(new King(pieceColor));
    


}

Board::Board(){

    //Initialize the game board
    createBoard();

    initializePieces(WHITE);

    initializePieces(BLACK);
}

Board::~Board(){
}