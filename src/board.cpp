#include "Board.hpp"
#include "pieces.cpp"

Board::Board(){

    //Initialize the game board
    createBoard();

    initializePieces(WHITE);

    initializePieces(BLACK);
}

Board::~Board(){
}

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

void Board::calc_moves(Piece* selectedPiece, int row, int col){
    PIECE_TYPE selectedPieceType = selectedPiece->getPieceType();

    switch (selectedPieceType)
    {
    case 0://PAWN
    {   Pawn_Moves(selectedPiece,row,col);
        break;
    }
    case 1://KING
    {   
        King_Moves(selectedPiece,row,col);
        break;
    }
    case 2://QUEEN
    {   
        std::vector<std::vector<int>>increments = {{-1,1} , {-1,-1} , {1,1} , {1,-1}, {-1,0} , {0,1} , {1,0} , {0,-1}};
        Straight_line_Moves(selectedPiece,row,col,increments);
        break;
    }
    case 3://BISHOP
    {
        std::vector<std::vector<int>>increments = {{-1,1} , {-1,-1} , {1,1} , {1,-1}};
        Straight_line_Moves(selectedPiece,row,col,increments);
        break;
    }
    case 4://KNIGHT
    {
        Knight_Moves(selectedPiece,row,col);
        break;
    }
    case 5://ROOK
        {
            std::vector<std::vector<int>>increments = {{-1,0} , {0,1} , {1,0} , {0,-1}};
            Straight_line_Moves(selectedPiece,row,col,increments);
            break;
        }
    }
}

void Board::Knight_Moves(Piece *SelectedPiece, int row,int col){
    // 8 Possible moves for knight
    Color selectedPieceColor = SelectedPiece->getPieceColor();

    std::vector<std::vector<int>> possible_moves = 
    {
        {row+2,col+1},{row+2,col-1},
        {row+1,col+2},{row-1,col+2},
        {row-2,col+1},{row-2,col-1},
        {row+1,col-2},{row-1,col-2},

    };

    for(int i=0;i<(int)possible_moves.size();i++){
        int possibleRow = possible_moves[i][0];
        int possibleCol = possible_moves[i][1];

        if(Square::inRange(possibleRow,possibleCol)){
            if(gameBoard[possibleRow][possibleCol].empty_or_rival(selectedPieceColor)){
                // Create New Move
                // Square *initial = new Square(row,col);
                Vector2 initialSquarePos = {(float)row,(float)col};
                // Square *final = new Square(possibleRow,possibleCol);
                Vector2 finalSquarePos = {(float)possibleRow,(float)possibleCol};

                Move *move = new Move(initialSquarePos, finalSquarePos);
                
                // Add new move to possible moves list on piece
                SelectedPiece->addMoves(move);
            }

        }

    }   
}

void Board::Pawn_Moves(Piece *SelectedPiece, int row,int col){
    int steps = 1;
    int pieceDirection = SelectedPiece->getPieceDirection();
    Color selectedPieceColor = SelectedPiece->getPieceColor();

    if(!SelectedPiece->checkIfMoved())steps = 2;


    int start = row + pieceDirection;
    int end = row + (pieceDirection * (1+steps));

    

    std::vector<std::vector<int>> valid_moves;

    //Calculate the straight moves
    for(int possibleRow=start;possibleRow!=end;possibleRow+=pieceDirection){
        if(Square::inRange(possibleRow,col)){
            if(gameBoard[possibleRow][col].isEmpty()){
                
                // Create New Move
                // Square *initial = new Square(row,col);
                Vector2 initialSquarePos = {(float)row,(float)col};
                // Square *final = new Square(possibleRow,possibleCol);
                Vector2 finalSquarePos = {(float)possibleRow,(float)col};

                Move *move = new Move(initialSquarePos, finalSquarePos);
                
                // Add new move to possible moves list on piece
                SelectedPiece->addMoves(move);
            }else{
                break;
            }

        }else{
            break;
        }
    }

    //Calculate Diagonal Moves
    int possibleRow = row+pieceDirection;

    if(Square::inRange(possibleRow,col+1)){
        if(gameBoard[possibleRow][col+1].hasRivalPiece(selectedPieceColor)){
                
            // Create New Move
            // Square *initial = new Square(row,col);
            Vector2 initialSquarePos = {(float)row,(float)col};
            // Square *final = new Square(possibleRow,possibleCol);
            Vector2 finalSquarePos = {(float)possibleRow,(float)col+1};

            Move *move = new Move(initialSquarePos, finalSquarePos);
                
            // Add new move to possible moves list on piece
            SelectedPiece->addMoves(move);
        }
    }

    if(Square::inRange(possibleRow,col-1)){
        if(gameBoard[possibleRow][col-1].hasRivalPiece(selectedPieceColor)){
                
            // Create New Move
            // Square *initial = new Square(row,col);
            Vector2 initialSquarePos = {(float)row,(float)col};
            // Square *final = new Square(possibleRow,possibleCol);
            Vector2 finalSquarePos = {(float)possibleRow,(float)col-1};

            Move *move = new Move(initialSquarePos, finalSquarePos);
                
            // Add new move to possible moves list on piece
            SelectedPiece->addMoves(move);
        }
    }
}

void Board::Straight_line_Moves(Piece *SelectedPiece, int row,int col,std::vector<std::vector<int>>increments){
    Color selectedPieceColor = SelectedPiece->getPieceColor();

    for(auto inc:increments){
        int rowIncrements = inc[0];
        int colIncrements = inc[1];

        int possibleRow = row+rowIncrements;
        int possibleCol = col+colIncrements;

        while(true){
            if(Square::inRange(possibleRow,possibleCol)){
                Vector2 initialSquarePos = {(float)row,(float)col};

                Vector2 finalSquarePos = {(float)possibleRow,(float)possibleCol};

                Move *move = new Move(initialSquarePos, finalSquarePos);

                if(gameBoard[possibleRow][possibleCol].isEmpty()){
                    SelectedPiece->addMoves(move);
                }else if(gameBoard[possibleRow][possibleCol].hasRivalPiece(selectedPieceColor)){
                    SelectedPiece->addMoves(move);
                    break;
                }else{
                    break;
                }

                possibleRow += rowIncrements;
                possibleCol += colIncrements;
            }else{
                break;
            }
        }
    }
}

void Board::King_Moves(Piece* selectedPiece, int row, int col){
    Color selectedPieceColor = selectedPiece->getPieceColor();

    std::vector<std::vector<int>>possibleMoves = {
        {row-1,col},
        {row+1,col},
        {row+1,col+1},
        {row-1,col+1},
        {row,col+1},
        {row,col-1},
        {row-1,col-1},
        {row+1,col-1}
    };

    for(auto move: possibleMoves){
        int possibleRow = move[0];
        int possibleCol = move[1];

        if(Square::inRange(possibleRow,possibleCol)){
            if(gameBoard[possibleRow][possibleCol].empty_or_rival(selectedPieceColor)){
                // Create New Move
                Vector2 initialSquarePos = {(float)row,(float)col};
               
                Vector2 finalSquarePos = {(float)possibleRow,(float)possibleCol};

                Move *move = new Move(initialSquarePos, finalSquarePos);
                
                // Add new move to possible moves list on piece
                selectedPiece->addMoves(move);
            }
        }
    }

    // TODO: Casteling Moves

}

void Board::ProcessMove(Move* newMove){
    Vector2 initialPosition = newMove->getInitialSquare();
    Vector2 finalPosition = newMove->getFinalSquare();


    // console board move update
    if(gameBoard[finalPosition.y][finalPosition.x].getPiece()){
        gameBoard[finalPosition.y][finalPosition.x].deletePiece();
    }

    gameBoard[finalPosition.y][finalPosition.x].setPiece((std::move(gameBoard[initialPosition.y][initialPosition.x].getPiece())));

    gameBoard[initialPosition.y][initialPosition.x].setPiece(nullptr);

    gameBoard[finalPosition.y][finalPosition.x].piece->clearMoveVector();

    gameBoard[finalPosition.y][finalPosition.x].piece->setMoved();

    gameBoard[finalPosition.y][finalPosition.x].piece->setLastMove(newMove);



}

bool Board::ValidateMove(Piece* selectedPiece, Move* move){
    int finalSquareRow = move->getFinalSquare().x;
    int finalSquareCol = move->getFinalSquare().y;

    for(auto possibleMoves:selectedPiece->getMoveVector()){

        int possibleRow = possibleMoves->getFinalSquare().y;
        int possibleCol = possibleMoves->getFinalSquare().x; 

        if(possibleRow == finalSquareRow && possibleCol == finalSquareCol)return true;
    }

    return false;
}