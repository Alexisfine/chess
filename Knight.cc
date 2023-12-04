#include "Knight.h"

Knight::Knight(ChessColor color) :
        ChessPiece{ChessType::KNIGHT, color} {}

MoveResult Knight::isMovePossiblyValid(ChessBoard& board, const Move& move) {
    std::vector<ValidMove> possibleValidMoves = getAvailableMoves(board, move.getStart(), true);
    for (auto validMove : possibleValidMoves) {
        if (move.getStart() == validMove.getStart() && move.getEnd() == validMove.getEnd()) return {true, false};
    }
    return {false, false};
}

std::vector<ValidMove> Knight::getAvailableMoves(ChessBoard& board, const Position& curPosition, bool check) {
    std::vector<ValidMove> moves;
    int dir[8][2] = {{1,2}, {1,-2}, {-1,-2},{-1,2},{2,1},{2,-1},{-2,1},{-2,-1}};

    for (auto pos : dir) {
        Position newPosition {curPosition.getRow() + pos[0], curPosition.getCol() + pos[1]};
        if (!board.isValidPos(newPosition)) continue; // check if newPosition is within the grid
        // check if newPosition is occupied by myself
        if (!board.isPositionEmpty(newPosition) && board.isPositionOccupiedByColor(newPosition, color)) continue;
        Move move {curPosition, newPosition, this};
        ChessColor opponentColor = color == ChessColor::WHITE ? ChessColor::BLACK : ChessColor::WHITE;
        bool canCheck = check && board.simulateMove(move, opponentColor);
        int beCapturedScore = check ? board.simulateCapture(move, color).score : 0;
        bool canCapture = false;
        if (!board.isPositionEmpty(newPosition)) canCapture = true;
        ValidMove possibleMove {curPosition, newPosition, this, canCapture, canCheck,
                                canCapture ? board.getCellAtPos(newPosition).getChessPiece()->getScore() : 0,
                                beCapturedScore};
        if (check) {
            bool willCheck = board.simulateMove(possibleMove, color);
            if (!willCheck) {
                moves.emplace_back(possibleMove);
            }
        } else moves.emplace_back(possibleMove);
    }
    return moves;
}
