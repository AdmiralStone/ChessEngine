#include "Piece.hpp"

Piece::Piece(/* args */)
{
}

Piece::~Piece()
{
    UnloadTexture(texture);
}


void Piece::setTexture(){
    std::string assetPath = "./assets/images/imgs-80px/";

    if(ColorEq(color,WHITE)){
        assetPath += "white_" + name + ".png";
        
    }else{
        assetPath += "black_" + name + ".png";
        
    }

    Image image = LoadImage(assetPath.c_str());
    texture = LoadTextureFromImage(image);
    UnloadImage(image);
}


