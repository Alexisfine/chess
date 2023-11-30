#include "ChessPiece.h"
ChessPiece::ChessPiece(ChessType type, ChessColor color) :
    type{type}, color{color}, used{false}, totalMoves{0} {}

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


void ChessPiece::incrementTotalMoves() {
    totalMoves++;
}

int ChessPiece::getTotalMoves() const {
    return totalMoves;
}

bool operator==(const ChessPiece& a, const ChessPiece& b) {
    return a.getType() == b.getType();
}

