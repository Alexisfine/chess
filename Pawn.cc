#include "Pawn.h"

Pawn::Pawn(ChessBoard& board, Player& owner) :
        ChessPiece{ChessType::PAWN, board, owner} {}

bool Pawn::isMovePossiblyValid(const Move& move) {
    std::vector<ValidMove> possibleValidMoves = getAvailableMoves(move.getStart());
    for (auto validMove : possibleValidMoves) {
        if (move.getStart() == validMove.getStart() && move.getEnd() == validMove.getEnd()) return true;
    }
    return false;
}

std::vector<ValidMove> Pawn::getAvailableMoves(const Position& curPosition) {
    std::vector<ValidMove> moves;
    Position newPosition {curPosition.getRow() + 1, curPosition.getCol() + 1};
    if (!board.isValidPos(newPosition)) return moves; // check if newPosition is within the grid
    if (!board.isPositionEmpty(newPosition)) return moves;

    bool canCapture = false;
    bool canCheck = false;
    ValidMove possibleMove {curPosition, newPosition, this, canCapture, canCheck};
    moves.emplace_back(possibleMove);
}

