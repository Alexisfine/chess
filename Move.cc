#include "Move.h"

Move::Move(Position start, Position end, const ChessPiece* chessPiece) :
    start{start},end{end}, chessPiece{chessPiece} {}

const Position& Move::getStart() const{
    return start;
}
const Position& Move::getEnd() const{
    return end;
}
const ChessPiece* Move::getChessPiece() const{
    return chessPiece;
}
