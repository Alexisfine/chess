#include "King.h"

King::King(ChessBoard& board, Player& owner) :
        ChessPiece{ChessType::KING, board, owner} {}

bool King::isMovePossiblyValid(const Move& move) {
    std::vector<ValidMove> possibleValidMoves = getAvailableMoves(move.getStart());
    for (auto validMove : possibleValidMoves) {
        if (move.getStart() == validMove.getStart() && move.getEnd() == validMove.getEnd()) return true;
    }
    return false;
}
std::vector<ValidMove> King::getAvailableMoves(const Position& curPosition) {
    int possibleMoves[8][2] = {{1,0},{-1,0},{0,1},{0,-1},{-1,-1},{-1,1},{1,-1},{1,1}};
    std::vector<ValidMove> moves;
    for (auto pos : possibleMoves) {
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