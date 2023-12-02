#include "Square.hpp"



Square::Square(int row, int col ){
    square_row_pos = row;
    square_col_pos = col;
    piece = nullptr;

}

Square::~Square(){
    delete piece;
}

void Square::setPiece(Piece *piece){
    this->piece = piece;

}

bool Square::hasPiece(){ 
    if(piece != NULL){
        return true;
    }
    return false;
}

void Square::Draw(){
    // piece->setTexture(size);

    // Get height and width of the piece texture
    int textureWidth = piece->texture.width;
    int textureHeight = piece->texture.height;

    float textureX = square_col_pos * SQUARE_SIZE + (SQUARE_SIZE - textureWidth) / 2;
    float textureY = square_row_pos * SQUARE_SIZE + (SQUARE_SIZE - textureHeight) / 2;

    DrawTexture(piece->texture,textureX,textureY,WHITE);
}

bool Square::inRange(int row, int col){
    if(row < 0 || row > 7)return false;

    if(col < 0 || col > 7)return false;

    return true;
} 

bool Square::isEmpty(){
    return !hasPiece();
}

bool Square::hasRivalPiece(Color selectedPieceColor){
    if(hasPiece()){
        if(!ColorEq(selectedPieceColor,piece->getPieceColor())){
            return true;
        }
    }
    return false;
};

bool Square::hasTeamPiece(Color selectedPieceColor){
    if(ColorEq(selectedPieceColor,piece->getPieceColor())){
        return true;
    }

    return false;
}

bool Square::empty_or_rival(Color selectedPieceColor){
    return isEmpty() || hasRivalPiece(selectedPieceColor);
}
