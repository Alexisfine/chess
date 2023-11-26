#include "King.h"

King::King(ChessBoard& board, Player& owner) :
        ChessPiece{ChessType::KING, board, owner} {}

bool King::isMovePossiblyValid(const Move& move) const {
    int rowDiff = std::abs(move.getStart().getRow() - move.getEnd().getRow());
    int colDiff = std::abs(move.getStart().getCol() - move.getEnd().getCol());
    // check if this move moves 1 square position
    if (rowDiff > 1 || colDiff > 1) return false;
    if (rowDiff + colDiff == 0) return false;

    // check if the new position is occupied by player's own chess
    if (!board.isPositionEmpty(move.getEnd()) && board.isPositionOccupiedByPlayer(move.getEnd(), owner)) return false;

    return true;
}
std::vector<ValidMove> King::getAvailableMoves(const Position& curPosition)  {
    std::vector<ValidMove> moves;
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0) continue;
            Position newPosition {curPosition.getRow() + dx, curPosition.getCol() + dy};
            if (!board.isValidPos(newPosition)) continue; // check if newPosition is within the grid
            // check if newPosition is occupied by myself
            if (!board.isPositionEmpty(newPosition) && board.isPositionOccupiedByPlayer(newPosition, owner)) continue;

            bool canCheck = false; // TODO Implement Check
            bool canCapture = false;
            if (!board.isPositionEmpty(newPosition)) canCapture = true;
            ValidMove possibleMove {curPosition, newPosition, this, canCapture, canCheck};
            moves.emplace_back(possibleMove);
        }
    }
    return moves;
}