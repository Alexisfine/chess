#include "Move.h"

Move::Move(Position start, Position end, ChessPiece* chessPiece) :
    start{start},end{end}, chessPiece{chessPiece} {}

const Position& Move::getStart() const{
    return start;
}
const Position& Move::getEnd() const{
    return end;
}
ChessPiece* Move::getChessPiece() {
    return chessPiece;
}
