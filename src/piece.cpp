#include "Piece.hpp"

Piece::Piece(/* args */)
{
}

Piece::~Piece()
{
    UnloadTexture(texture);
}


void Piece::setTexture(int size){
    std::string assetPath = "./assets/images/imgs-";

    assetPath+= std::to_string(size)+"px/";

    if(ColorEq(color,WHITE)){
        assetPath += "white_" + name + ".png";
        
    }else{
        assetPath += "black_" + name + ".png";
        
    }

    Image image = LoadImage(assetPath.c_str());
    texture = LoadTextureFromImage(image);
    UnloadImage(image);
}

PIECE_TYPE Piece::getPieceType(){
    return PieceType;
}

Color Piece::getPieceColor(){
    return color;
}

void Piece::addMoves(Move* validMove){
    validMoves.push_back(validMove);
}

std::vector<Move*> Piece::getMoveVector(){
    return validMoves;
};

bool Piece::checkIfMoved(){
    return moved;
}

int Piece::getPieceDirection(){
    return direction;
}

void Piece::setMoved(){
    moved = true;
}


