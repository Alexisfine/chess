#include "Knight.h"

Knight::Knight(ChessBoard& board, Player& owner) :
        ChessPiece{ChessType::KNIGHT, board, owner} {}

bool Knight::isMovePossiblyValid(const Move& move) {
    std::vector<ValidMove> possibleValidMoves = getAvailableMoves(move.getStart());
    for (auto validMove : possibleValidMoves) {
        if (move.getStart() == validMove.getStart() && move.getEnd() == validMove.getEnd()) return true;
    }
    return false;
}

std::vector<ValidMove> Knight::getAvailableMoves(const Position& curPosition) {
    std::vector<ValidMove> moves;
    int dir[8][2] = {{1,2}, {1,-2}, {-1,-2},{-1,2},{2,1},{2,-1},{-2,1},{-2,-1}};

    for (auto pos : dir) {
        Position newPosition {curPosition.getRow() + pos[0], curPosition.getCol() + pos[1]};
        if (!board.isValidPos(newPosition)) continue; // check if newPosition is within the grid
        // check if newPosition is occupied by myself
        if (!board.isPositionEmpty(newPosition) && board.isPositionOccupiedByPlayer(newPosition, owner)) continue;
        bool canCheck = false; //  Implement Check Later
        bool canCapture = false;
        if (!board.isPositionEmpty(newPosition)) canCapture = true;
        ValidMove possibleMove {curPosition, newPosition, this, canCapture, canCheck};
        moves.emplace_back(possibleMove);
    }
    return moves;
}
