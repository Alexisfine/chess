#ifndef CHESS_MOVE_H
#define CHESS_MOVE_H


#include "Position.h"
class ChessPiece;

class Move {
protected:
    Position start;
    Position end;
    ChessPiece* chessPiece;
public:
    Move(Position start, Position end, ChessPiece* chessPiece);
    const Position& getStart() const;
    const Position& getEnd() const;
    ChessPiece* getChessPiece();
};


#endif //CHESS_MOVE_H
