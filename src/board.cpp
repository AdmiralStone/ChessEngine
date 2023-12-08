#include "Board.hpp"
#include "pieces.cpp"

Board::Board(){
    InitAudioDevice();

    movePieceSound = LoadSound("./assets/sounds/move.wav");
    capturePieceSound = LoadSound("./assets/sounds/capture.wav");

    //Initialize the game board
    createBoard();

    initializePieces(WHITE);

    initializePieces(BLACK);
}

Board::~Board(){
    if(lastMove)delete lastMove;

    CloseAudioDevice();
    UnloadSound(movePieceSound);
    UnloadSound(capturePieceSound);
}

Board::Board(const Board& boardOriginal){
    for (const auto& row : boardOriginal.gameBoard) {
    gameBoard.emplace_back();
    gameBoard.back().reserve(row.size());
    for (const auto& square : row) {
        Square *squareCopy = new Square(square);
        gameBoard.back().emplace_back(*squareCopy);
    }
  }
    
    movePieceSound = boardOriginal.movePieceSound;
    capturePieceSound = boardOriginal.movePieceSound;
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

void Board::calc_moves(Piece* selectedPiece, int row, int col, bool checkPotential){
    PIECE_TYPE selectedPieceType = selectedPiece->getPieceType();

    switch (selectedPieceType)
    {
    case 0://PAWN
    {   Pawn_Moves(selectedPiece,row,col,checkPotential);
        break;
    }
    case 1://KING
    {   
        King_Moves(selectedPiece,row,col,checkPotential);
        break;
    }
    case 2://QUEEN
    {   
        std::vector<std::vector<int>>increments = {{-1,1} , {-1,-1} , {1,1} , {1,-1}, {-1,0} , {0,1} , {1,0} , {0,-1}};
        Straight_line_Moves(selectedPiece,row,col,increments,checkPotential);
        break;
    }
    case 3://BISHOP
    {
        std::vector<std::vector<int>>increments = {{-1,1} , {-1,-1} , {1,1} , {1,-1}};
        Straight_line_Moves(selectedPiece,row,col,increments,checkPotential);
        break;
    }
    case 4://KNIGHT
    {
        Knight_Moves(selectedPiece,row,col,checkPotential);
        break;
    }
    case 5://ROOK
        {
            std::vector<std::vector<int>>increments = {{-1,0} , {0,1} , {1,0} , {0,-1}};
            Straight_line_Moves(selectedPiece,row,col,increments,checkPotential);
            break;
        }
    }
}

void Board::Knight_Moves(Piece *SelectedPiece, int row,int col, bool checkPotential){
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
                Vector2 initialSquarePos = {(float)col,(float)row};
                // Square *final = new Square(possibleRow,possibleCol);
                Vector2 finalSquarePos = {(float)possibleCol,(float)possibleRow};

                Move *move = new Move(initialSquarePos, finalSquarePos);
                
                if(checkPotential){
                    if(!moveLeadsToCheck(SelectedPiece,move)){
                        // Add new move to possible moves list on piece
                        SelectedPiece->addMoves(move);
                    }else{
                        break;
                    }
                }else{
                    // Add new move to possible moves list on piece
                    SelectedPiece->addMoves(move);
                }  
            }

        }

    }   
}

void Board::Pawn_Moves(Piece *SelectedPiece, int row,int col, bool checkPotential){
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
                Vector2 initialSquarePos = {(float)col,(float)row};
                
                Vector2 finalSquarePos = {(float)col,(float)possibleRow};

                Move* move = new Move(initialSquarePos, finalSquarePos);
                if(checkPotential){
                    if(!moveLeadsToCheck(SelectedPiece,move)){
                        // Add new move to possible moves list on piece
                        SelectedPiece->addMoves(move);
                    }
                }else{
                    // Add new move to possible moves list on piece
                    SelectedPiece->addMoves(move);
                }  
                
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
            Vector2 initialSquarePos = {(float)col,(float)row};
            // Square *final = new Square(possibleRow,possibleCol);
            Vector2 finalSquarePos = {(float)col+1,(float)possibleRow};

            Move *move = new Move(initialSquarePos, finalSquarePos);
                
            if(checkPotential){
                if(!moveLeadsToCheck(SelectedPiece,move)){
                    // Add new move to possible moves list on piece
                    SelectedPiece->addMoves(move);
                }
            }else{
                // Add new move to possible moves list on piece
                SelectedPiece->addMoves(move);
            }  
        }
    }

    if(Square::inRange(possibleRow,col-1)){
        if(gameBoard[possibleRow][col-1].hasRivalPiece(selectedPieceColor)){
                
            // Create New Move
            // Square *initial = new Square(row,col);
            Vector2 initialSquarePos = {(float)col,(float)row};
            // Square *final = new Square(possibleRow,possibleCol);
            Vector2 finalSquarePos = {(float)col-1,(float)possibleRow};

            Move *move = new Move(initialSquarePos, finalSquarePos);
         
            if(checkPotential){
                if(!moveLeadsToCheck(SelectedPiece,move)){
                    // Add new move to possible moves list on piece
                    SelectedPiece->addMoves(move);
                }
            }else{
                // Add new move to possible moves list on piece
                SelectedPiece->addMoves(move);
            }
        }
    }
}

void Board::Straight_line_Moves(Piece *SelectedPiece, int row,int col,std::vector<std::vector<int>>increments,bool checkPotential){
    Color selectedPieceColor = SelectedPiece->getPieceColor();

    for(auto inc:increments){
        int rowIncrements = inc[0];
        int colIncrements = inc[1];

        int possibleRow = row+rowIncrements;
        int possibleCol = col+colIncrements;

        while(true){
            if(Square::inRange(possibleRow,possibleCol)){
                Vector2 initialSquarePos = {(float)col,(float)row};

                Vector2 finalSquarePos = {(float)possibleCol,(float)possibleRow};

                Move *move = new Move(initialSquarePos, finalSquarePos);

                if(gameBoard[possibleRow][possibleCol].isEmpty()){
                    if(checkPotential){
                        if(!moveLeadsToCheck(SelectedPiece,move)){
                            // Add new move to possible moves list on piece
                            SelectedPiece->addMoves(move);
                        }else{
                            break;
                        }
                    }else{
                        // Add new move to possible moves list on piece
                        SelectedPiece->addMoves(move);
                    }  
                }else if(gameBoard[possibleRow][possibleCol].hasRivalPiece(selectedPieceColor)){
                    if(checkPotential){
                        if(!moveLeadsToCheck(SelectedPiece,move)){
                            // Add new move to possible moves list on piece
                            SelectedPiece->addMoves(move);
                        }else{
                            break;
                        }
                    }else{
                        // Add new move to possible moves list on piece
                        SelectedPiece->addMoves(move);
                    }  
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

void Board::King_Moves(Piece* selectedPiece, int row, int col, bool checkPotential){
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
                Vector2 initialSquarePos = {(float)col,(float)row};
               
                Vector2 finalSquarePos = {(float)possibleCol,(float)possibleRow};

                Move *move = new Move(initialSquarePos, finalSquarePos);
                
                if(checkPotential){
                    if(!moveLeadsToCheck(selectedPiece,move)){
                        // Add new move to possible moves list on piece
                        selectedPiece->addMoves(move);
                    }else{
                        break;
                    }
                }else{
                    // Add new move to possible moves list on piece
                    selectedPiece->addMoves(move);
                }
            }
        }
    }

    // TODO: Casteling Moves

}

void Board::ProcessMove(Move* newMove,int currentPlayer, bool virtualProcess){
    Vector2 initialPosition = newMove->getInitialSquare();
    Vector2 finalPosition = newMove->getFinalSquare();

    Color currentPlayerColor;
    bool hadEnemyPiece = false;

    if(currentPlayer == PLAYER_ONE){
        currentPlayerColor = WHITE;
    }else{
        currentPlayerColor = BLACK;
    }

    // console board move update
    if(!virtualProcess && gameBoard[finalPosition.y][finalPosition.x].getPiece()){
        if(gameBoard[finalPosition.y][finalPosition.x].hasRivalPiece(currentPlayerColor))hadEnemyPiece = true;

        gameBoard[finalPosition.y][finalPosition.x].deletePiece();
    }

    gameBoard[finalPosition.y][finalPosition.x].setPiece((std::move(gameBoard[initialPosition.y][initialPosition.x].getPiece())));

    gameBoard[initialPosition.y][initialPosition.x].setPiece(nullptr);

    gameBoard[finalPosition.y][finalPosition.x].piece->clearMoveVector();

    gameBoard[finalPosition.y][finalPosition.x].piece->setMoved();

    if(gameBoard[finalPosition.y][finalPosition.x].piece->getPieceType() == 0){
        check_pawn_promotion(finalPosition, currentPlayerColor);
    }

    if(hadEnemyPiece){
        PlaySound(capturePieceSound);
    }else{
        PlaySound(movePieceSound);
    }

    lastMove = newMove;

}

void Board::check_pawn_promotion(Vector2 finalSquare, Color pieceColor){
    if(finalSquare.y == 0 || finalSquare.y == 7){
        gameBoard[finalSquare.y][finalSquare.x].deletePiece();

        gameBoard[finalSquare.y][finalSquare.x].setPiece(new Queen(pieceColor));
    }
}

bool Board::moveLeadsToCheck(Piece* selectedPiece,Move* move){
    Board* copyBoard = new Board(*this);
    Piece* copyPiece = new Piece(*selectedPiece);
    
    //Check which color piece is being moved
    int currentPlayer;
    if(ColorEq(copyPiece->getPieceColor(),WHITE)){
        currentPlayer = PLAYER_ONE;
    }else{
        currentPlayer = PLAYER_TWO;
    }

    

    // Piece is moved to next square in our virtual copy board.
    // Send YES for virtualProcess variable in ProcessMove
    copyBoard->ProcessMove(move,currentPlayer,true); 
    
    //Now for all enemey pieces check if their suggested moves lead to the king
    for(int row = 0; row<ROWS;row++){
        for(int col = 0;col<COLS;col++){
            if(copyBoard->gameBoard[row][col].hasRivalPiece(copyPiece->getPieceColor())){
                //Get the enemy piece on a particular square
                Piece* virtualPiece = copyBoard->gameBoard[row][col].getPiece();

                // For that enemy piece calculate all its possible moves
                copyBoard->calc_moves(virtualPiece,row,col,false);

                //Get array of all possible moves for that piece
                for(auto move:virtualPiece->getMoveVector()){
                    // Get the final square for each move
                    Vector2 finalSquare = move->getFinalSquare();

                    // Check if the piece on the final square is a King
                    if(copyBoard->gameBoard[finalSquare.y][finalSquare.x].hasRivalPiece(virtualPiece->getPieceColor()) && copyBoard->gameBoard[finalSquare.y][finalSquare.x].getPiece()->getPieceType() == 1){
                        return true; 
                    }
                }
            }
        }
    }

    return false;
}

bool Board::ValidateMove(Piece* selectedPiece, Move* move){
    int finalSquareRow = move->getFinalSquare().y;
    int finalSquareCol = move->getFinalSquare().x;

    for(auto possibleMoves:selectedPiece->getMoveVector()){

        int possibleRow = possibleMoves->getFinalSquare().y;
        int possibleCol = possibleMoves->getFinalSquare().x; 

        if(possibleRow == finalSquareRow && possibleCol == finalSquareCol)return true;
    }

    return false;
}

Move* Board::getLastMove(){
    return lastMove;
}

void Board::Reset(){
    lastMove = nullptr;
    gameBoard.clear();

    createBoard();

    initializePieces(WHITE);

    initializePieces(BLACK);
}