#include "Pawn.h"

Pawn::Pawn(ChessBoard& board, Player& owner) :
        ChessPiece{ChessType::PAWN, board, owner} {
    switch (owner.getPlayerNo()) {
        case 0:
            moveDx = 0;
            moveDy = 1;
            break;
        case 1:
            moveDx = 0;
            moveDy = -1;
            break;
        case 2:
            moveDx = 1;
            moveDy = 0;
            break;
        case 3:
            moveDx = -1;
            moveDy = 0;
            break;
    }
}

bool Pawn::isMovePossiblyValid(const Move& move) {
    std::vector<ValidMove> possibleValidMoves = getAvailableMoves(move.getStart());
    for (auto validMove : possibleValidMoves) {
        if (move.getStart() == validMove.getStart() && move.getEnd() == validMove.getEnd()) return true;
    }
    return false;
}

std::vector<ValidMove> Pawn::getAvailableMoves(const Position& curPosition) {
    std::vector<ValidMove> moves;
    Position newPosition {curPosition.getRow() + moveDy, curPosition.getCol() + moveDx};
    if (!board.isValidPos(newPosition)) return moves; // check if newPosition is within the grid
    if (!board.isPositionEmpty(newPosition)) return moves;

    bool canCapture = false;
    bool canCheck = false;
    ValidMove possibleMove {curPosition, newPosition, this, canCapture, canCheck};
    moves.emplace_back(possibleMove);
}

