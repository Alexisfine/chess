#ifndef CHESS_MOVE_H
#define CHESS_MOVE_H


#include "Position.h"
#include "ChessPiece.h"
#include <memory>

class Move {
    Position& start;
    Position& end;
    ChessPiece* chessPiece;
public:
    Move(Position& start, Position& end, ChessPiece* chessPiece);
};


#endif //CHESS_MOVE_H
