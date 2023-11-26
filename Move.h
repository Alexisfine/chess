#ifndef CHESS_MOVE_H
#define CHESS_MOVE_H


#include "Position.h"
#include "ChessPiece.h"
#include <memory>

class Move {
    Position start;
    Position end;
    const ChessPiece* chessPiece;
public:
    Move(Position start, Position end, const ChessPiece* chessPiece);
    const Position& getStart() const;
    const Position& getEnd() const;
    const ChessPiece* getChessPiece() const;
    friend bool operator==(const Move& a, const Move& b);
};

bool operator==(const Move& a, const Move& b);

#endif //CHESS_MOVE_H
