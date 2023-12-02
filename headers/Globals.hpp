#pragma once

//FPS
const int TARGET_FPS = 60;

//Screen Dimensions
const int WIN_HEIGHT = 800;
const int WIN_WIDTH = 800;

//Board Dimension
const int COLS = 8;
const int ROWS = 8;
const int SQUARE_SIZE = WIN_WIDTH / COLS;


//Piece Types
enum PIECE_TYPE{
    PAWN,
    KING,
    QUEEN,
    BISHOP,
    KNIGHT,
    ROOK
};
