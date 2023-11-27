
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
    virtual bool makeMove(const Move& move, const Player& player) = 0;
    virtual bool isMoveLegal(const Move& move, const Player& player) const = 0;
    virtual bool isValidPos(const Position& pos) const = 0;
    bool isPositionEmpty(const Position& pos) const;
    bool isPositionOccupiedByPlayer(const Position& pos, const Player& player) const;
    const Cell& getCellAtPos(const Position& pos) const;
    void setPieceAtPosition(const Position& pos, ChessPiece& piece);
    void removePieceAtPosition(const Position& pos);
    int getDimension() const;
};

#endif //CHESS_CHESSBOARD_H
