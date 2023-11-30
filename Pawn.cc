#include "Pawn.h"

Pawn::Pawn(ChessColor color) :
        ChessPiece{ChessType::PAWN, color} {
    switch (color) {
        case ChessColor::WHITE:
            moveDx = 0;
            moveDy = 1;
            capture1x = -1;
            capture1y = 1;
            capture2x = 1;
            capture2y = 1;
            break;
        case ChessColor::BLACK:
            moveDx = 0;
            moveDy = -1;
            capture1x = -1;
            capture1y = -1;
            capture2x = 1;
            capture2y = -1;
            break;
        case ChessColor::RED:
            moveDx = 1;
            moveDy = 0;
            capture1x = 1;
            capture1y = 1;
            capture2x = 1;
            capture2y = -1;
            break;
        case ChessColor::BLUE:
            moveDx = -1;
            moveDy = 0;
            capture1x = -1;
            capture1y = 1;
            capture2x = -1;
            capture2y = -1;
            break;
    }
}

bool Pawn::isMovePossiblyValid(ChessBoard& board, const Move& move) {
    std::vector<ValidMove> possibleValidMoves = getAvailableMoves(board, move.getStart(), true);
    for (auto validMove : possibleValidMoves) {
        if (move.getStart() == validMove.getStart() && move.getEnd() == validMove.getEnd()) return true;
    }
    return false;
}

std::vector<ValidMove> Pawn::getAvailableMoves(ChessBoard& board, const Position& curPosition, bool check) {
    std::vector<ValidMove> moves;
    Position newPosition {curPosition.getRow() + moveDy, curPosition.getCol() + moveDx};
    if (!board.isPositionEmpty(newPosition)) return moves;

    bool canCheck = false;
    if (board.isValidPos(newPosition) && board.isPositionEmpty(newPosition)) {
        ValidMove possibleMove {curPosition, newPosition, this, false, canCheck};
        if (check) {
            bool willCheck = board.simulateMove(possibleMove, color);
            if (!willCheck) {
                moves.emplace_back(possibleMove);
            }
        } else moves.emplace_back(possibleMove);
    }


    if (firstMove) {
        Position newPosition2 {curPosition.getRow() + moveDy * 2, curPosition.getCol() + moveDx * 2};
        if (board.isValidPos(newPosition) && board.isPositionEmpty(newPosition) && board.isPositionEmpty(newPosition2)) {
            ValidMove possibleMove2 {curPosition, newPosition2, this, false, canCheck};
            if (check) {
                bool willCheck = board.simulateMove(possibleMove2, color);
                if (!willCheck) {
                    moves.emplace_back(possibleMove2);
                }
            } else moves.emplace_back(possibleMove2);
        }
    }

    // add capture logic
    Position capture1 = {curPosition.getRow() + capture1y, curPosition.getCol() + capture1x};
    if (board.isValidPos(capture1)) {
        if (!board.isPositionEmpty(capture1) && !board.isPositionOccupiedByColor(capture1, color)) {
            ValidMove captureMove1 {curPosition, capture1, this, true, canCheck};
            if (check) {
                bool willCheck = board.simulateMove(captureMove1, color);
                if (!willCheck) {
                    moves.emplace_back(captureMove1);
                }
            } else moves.emplace_back(captureMove1);
        }
    }
    Position capture2 = {curPosition.getRow() + capture2y, curPosition.getCol() + capture2x};
    if (board.isValidPos(capture2)) {
        if (!board.isPositionEmpty(capture2) && !board.isPositionOccupiedByColor(capture2, color)) {
            ValidMove captureMove2 {curPosition, capture2, this, true, canCheck};
            if (check) {
                bool willCheck = board.simulateMove(captureMove2, color);
                if (!willCheck) {
                    moves.emplace_back(captureMove2);
                }
            } else moves.emplace_back(captureMove2);
        }
    }

    return moves;
}

