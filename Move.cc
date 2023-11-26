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

bool operator==(const Move& a, const Move& b) {
    return a.start == b.start && a.end == b.end && a.chessPiece == b.chessPiece;
}