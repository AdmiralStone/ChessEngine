#include "Dragger.hpp"

void Dragger::updateMousePos(Vector2 mousePos){
    mouseX = mousePos.x;
    mouseY = mousePos.y;
}

void Dragger::saveInitPiecePos(Vector2 piecePos){
    initPieceRow = piecePos.y;
    initPieceCol = piecePos.x;
}

void Dragger::dragPiece(Piece* selectedPiece){
    this->selectedPiece = selectedPiece;
    dragging = true;
    this->selectedPiece->setTexture(128);
}

void Dragger::unDragPiece(){
    this->selectedPiece->setTexture(80);
    this->selectedPiece = NULL;
    dragging = false;
    
}

void Dragger::dragPiece(){
    int textureWidth = this->selectedPiece->texture.width;
    int textureHeight = this->selectedPiece->texture.height;

    
    float textureX = GetMouseX() - textureWidth/2;
    float textureY = GetMouseY() - textureHeight/2;

    DrawTexture(this->selectedPiece->texture,textureX,textureY,WHITE);
}

Dragger::Dragger(/* args */)
{
}

Dragger::~Dragger()
{
    delete selectedPiece;
}

void Dragger::Reset(){
    mouseX = 0;
    mouseY = 0;
    initPieceRow = 0;
    initPieceCol = 0;
    selectedPiece = nullptr;
    dragging = false;
}