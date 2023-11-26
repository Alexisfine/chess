#include "Move.h"

Move::Move(Position start, Position end, ChessPiece* chessPiece) :
    start{start},end{end}, chessPiece{chessPiece} {}

Position Move::getStart() {
    return start;
}
Position Move::getEnd() {
    return end;
}
ChessPiece* Move::getChessPiece() {
    return chessPiece;
}

bool operator==(const Move& a, const Move& b) {
    return a.start == b.start && a.end == b.end && a.chessPiece == b.chessPiece;
}