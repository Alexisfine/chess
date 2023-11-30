#include "ValidMove.h"

ValidMove::ValidMove(Position start, Position end, ChessPiece* chessPiece, bool canCapture, bool canCheck)
: Move{start, end, chessPiece}, canCapture{canCapture}, canCheck{canCapture}, enPassant{false} {}

bool ValidMove::operator<(const ValidMove& other) const {
    if (canCheck && !other.canCheck) return false;
    if (other.canCheck && !canCheck) return true;
    if (canCapture && !other.canCapture) return false;
    if (other.canCapture && !canCapture) return true;
    return true;
}

Position ValidMove::getStart() const {
    return start;
}

Position ValidMove::getEnd() const {
    return end;
}

void ValidMove::isEnPassant() {
    enPassant = true;
}
