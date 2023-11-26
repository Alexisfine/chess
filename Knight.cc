//
// Created by 薛景帝 on 2023/11/24.
//

#include "Knight.h"

Knight::Knight(ChessBoard& board, Player& owner) :
        ChessPiece{ChessType::KNIGHT, board, owner} {}

bool Knight::isMovePossiblyValid(const Move& move) const {
    std::vector<Move> possibleValidMoves = getAvailableMoves(move.getStart());
    for (auto validMove : possibleValidMoves) {
        if (move == validMove) return true;
    }
    return false;
}

std::vector<Move> Knight::getAvailableMoves(const Position& curPosition) const {
    std::vector<Move> moves;
    for (int dx = -2; dx <= 2; dx++) {
        if (dx == 0) continue;
        for (int dy = -2; dy <= 2; dy++) {
            if (dy == 0) continue;
            if ((abs(dx) == 2 && abs(dy) == 1) || (abs(dx) == 1 && abs(dy) == 2)) {
                Position newPosition {curPosition.getRow() + dx, curPosition.getCol() + dy};
                if (!board.isValidPos(newPosition)) continue; // check if newPosition is within the grid
                const Cell& cell = board.getCellAtPos(newPosition);
                ChessPiece* curChessPiece = cell.getChessPiece();
                if (&curChessPiece->getOwner() == &owner) continue; // position is occupied by player's own chess
                Move possibleMove {curPosition, newPosition, this};
                moves.emplace_back(possibleMove);
            }
        }
    }
    return moves;
}
