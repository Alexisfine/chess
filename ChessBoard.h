
#ifndef CHESS_CHESSBOARD_H
#define CHESS_CHESSBOARD_H

#include <vector>
#include "Cell.h"

class ChessBoard {
    int dimension;
    std::vector<std::vector<Cell>> board;
public:
    ChessBoard(int dimension);
    virtual void makeMove(Move move) = 0;
    virtual bool isMoveLegal(Move move) = 0;
    ChessType getPieceAtPosition(Position pos);
    void setPieceAtPosition(Position pos, ChessPiece* piece);
};

#endif //CHESS_CHESSBOARD_H
