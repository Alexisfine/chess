//
// Created by 薛景帝 on 2023/11/24.
//

#include "Pawn.h"

Pawn::Pawn(ChessBoard& board, Player& owner) :
        ChessPiece{ChessType::PAWN, board, owner} {}

bool Pawn::isMovePossiblyValid(const Move& move) const {
    std::vector<Move> possibleValidMoves = getAvailableMoves(move.getStart());
    for (auto validMove : possibleValidMoves) {
        if (move == validMove) return true;
    }
    return false;
}

std::vector<Move> Pawn::getAvailableMoves(const Position& curPosition) const {
    std::vector<Move> moves;
    Position newPosition {curPosition.getRow() + 1, curPosition.getCol() + 1};
    if (!board.isValidPos(newPosition)) return moves; // check if newPosition is within the grid
    const Cell& cell = board.getCellAtPos(newPosition);
    ChessPiece* curChessPiece = cell.getChessPiece();
    if (&curChessPiece->getOwner() == &owner) return moves; // position is occupied by player's own chess
    Move possibleMove {curPosition, newPosition, this};
    moves.emplace_back(possibleMove);
}