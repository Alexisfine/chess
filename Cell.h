#ifndef CHESS_CELL_H
#define CHESS_CELL_H


#include "ChessPiece.h"



class Cell {
    int row, col;
    ChessPiece* chessPiece;
public:
    Cell(int row, int col);
    ChessType getChess();
    void changeState(ChessType state, ChessPiece* newChessPiece);
    ChessType getChessType();
};

#endif //CHESS_CELL_H
