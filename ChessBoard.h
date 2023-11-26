
#ifndef CHESS_CHESSBOARD_H
#define CHESS_CHESSBOARD_H

#include <vector>
#include "Cell.h"

class ChessBoard {
protected:
    int dimension;
    std::vector<std::vector<Cell>> board;
public:
    ChessBoard(int dimension);
    virtual bool makeMove(const Move& move) = 0;
    virtual bool isMoveLegal(const Move& move) = 0;
    virtual bool isValidPos(const Position& pos) = 0;
    bool isPositionEmpty(const Position& pos);
    ChessPiece* getPieceAtPosition(const Position& pos);
    void setPieceAtPosition(const Position& pos, ChessPiece& piece);
};

#endif //CHESS_CHESSBOARD_H
