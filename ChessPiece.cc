#include "ChessPiece.h"
ChessPiece::ChessPiece(ChessType type, ChessBoard& board, Player& owner) :
    type{type}, board{board}, owner{owner}, alive{true} {}

ChessPiece::~ChessPiece() {
}

ChessType ChessPiece::getType() const {
    return type;
}

Player& ChessPiece::getOwner() {
    return owner;
}

bool ChessPiece::isAlive() const {
    return alive;
}

void ChessPiece::changeAliveState() {
    alive = !alive;
}

bool operator==(const ChessPiece& a, const ChessPiece& b) {
    return a.getType() == b.getType();
}