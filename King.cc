#include "King.h"

King::King(ChessBoard& board, Player& owner) :
        ChessPiece{ChessType::KING, board, owner} {}

bool King::isMovePossiblyValid(const Move& move) const {
    std::vector<Move> possibleValidMoves = getAvailableMoves(move.getStart());
    for (auto validMove : possibleValidMoves) {
        if (move == validMove) return true;
    }
    return false;
}
std::vector<Move> King::getAvailableMoves(const Position& curPosition) const {
    std::vector<Move> moves;
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0) continue;
            Position newPosition {curPosition.getRow() + dx, curPosition.getCol() + dy};
            if (!board.isValidPos(newPosition)) continue; // check if newPosition is within the grid
            const Cell& cell = board.getCellAtPos(newPosition);
            ChessPiece* curChessPiece = cell.getChessPiece();
            if (&curChessPiece->getOwner() == &owner) continue; // position is occupied by player's own chess
            Move possibleMove {curPosition, newPosition, this};
            moves.emplace_back(possibleMove);
        }
    }
    return moves;
}