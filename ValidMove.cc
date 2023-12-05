#include "ValidMove.h"

ValidMove::ValidMove(Position start, Position end, ChessPiece* chessPiece, bool canCapture, bool canCheck,
                     int capturedScore, int beCapturedScore)
: Move{start, end, chessPiece}, canCapture{canCapture}, canCheck{canCheck}, enPassant{false}, promotion{false},
capturedScore{capturedScore}, beCapturedScore{beCapturedScore} {}

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

bool ValidMove::getEnPassant() const {
    return enPassant;
}

bool ValidMove::getPromotion() {
    return promotion;
}

void ValidMove::setPromotion(bool p) {
    promotion = p;
}

bool ValidMove::getCanCapture() const {
    return canCapture;
}

bool ValidMove::getCanCheck() const {
    return canCheck;
}

int ValidMove::getCapturedScore() const {
    return capturedScore;
}
int ValidMove::getBeCapturedScore() const {
    return beCapturedScore;
}
