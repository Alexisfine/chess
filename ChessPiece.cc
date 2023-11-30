#include "ChessPiece.h"
ChessPiece::ChessPiece(ChessType type, ChessColor color) :
    type{type}, color{color}, used{false}, firstMove{true} {}

ChessPiece::~ChessPiece() {
}

ChessType ChessPiece::getType() const {
    return type;
}

//Player& ChessPiece::getOwner() {
//    return owner;
//}
ChessColor ChessPiece::getColor() const {
    return color;
}
bool ChessPiece::isUsed() const {
    return used;
}

void ChessPiece::setUsed(bool setUsed) {
    used = setUsed;
}


void ChessPiece::setFirstMoveToFalse() {
    firstMove = false;
}

bool operator==(const ChessPiece& a, const ChessPiece& b) {
    return a.getType() == b.getType();
}

