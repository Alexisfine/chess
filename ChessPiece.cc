#include "ChessPiece.h"
ChessPiece::ChessPiece(ChessType type, ChessBoard& board, Player& owner) :
    type{type}, board{board}, owner{owner}, alive{true} {}

ChessPiece::~ChessPiece() {
}

ChessType ChessPiece::getType() const {
    return type;
}
bool ChessPiece::isAlive() const {
    return alive;
}

void ChessPiece::changeAliveState() {
    alive = !alive;
}