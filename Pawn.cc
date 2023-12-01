#include "Pawn.h"

Pawn::Pawn(ChessColor color) :
        ChessPiece{ChessType::PAWN, color}, justMadeDoubleStep{false} {
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

MoveResult Pawn::isMovePossiblyValid(ChessBoard& board, const Move& move) {
    std::vector<ValidMove> possibleValidMoves = getAvailableMoves(board, move.getStart(), true);
    for (auto validMove : possibleValidMoves) {
        if (move.getStart() == validMove.getStart() && move.getEnd() == validMove.getEnd()) {
            if (validMove.getPromotion()) {
                return {true, true};
            } else return {true, false};
        }
    }
    return {false, false};
}

std::vector<ValidMove> Pawn::getAvailableMoves(ChessBoard& board, const Position& curPosition, bool check) {
    std::vector<ValidMove> moves;
    Position newPosition {curPosition.getRow() + moveDy, curPosition.getCol() + moveDx};
    if (board.isValidPos(newPosition) && board.isPositionEmpty(newPosition)) {
        ValidMove possibleMove {curPosition, newPosition, this, false, false};
        if (checkPromotion(newPosition)) possibleMove.setPromotion(true);
        if (check) {
            bool willCheck = board.simulateMove(possibleMove, color);
            if (!willCheck) moves.emplace_back(possibleMove);
        } else moves.emplace_back(possibleMove);
    }

    bool canCheck = false;
//    if (board.isValidPos(newPosition) && board.isPositionEmpty(newPosition)) {
//        ValidMove possibleMove {curPosition, newPosition, this, false, canCheck};
//        if (check) {
//            bool willCheck = board.simulateMove(possibleMove, color);
//            if (!willCheck) {
//                moves.emplace_back(possibleMove);
//            }
//        } else moves.emplace_back(possibleMove);
//    }


    if ((color == ChessColor::WHITE && curPosition.getRow() == 2) || (color == ChessColor::BLACK && curPosition.getRow() == 7)) {
        Position newPosition2 {curPosition.getRow() + moveDy * 2, curPosition.getCol() + moveDx * 2};
        if (board.isValidPos(newPosition2) && board.isPositionEmpty(newPosition) && board.isPositionEmpty(newPosition2)) {
            ValidMove possibleMove2 {curPosition, newPosition2, this, false, canCheck};
            if (checkPromotion(newPosition2)) possibleMove2.setPromotion(true);
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
            if (checkPromotion(capture1)) captureMove1.setPromotion(true);
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
            if (checkPromotion(capture2)) captureMove2.setPromotion(true);
            if (check) {
                bool willCheck = board.simulateMove(captureMove2, color);
                if (!willCheck) {
                    moves.emplace_back(captureMove2);
                }
            } else moves.emplace_back(captureMove2);
        }
    }

    // add en passant logic
    if (color == ChessColor::WHITE && curPosition.getRow() == 5) {
        // check left cell
        Position leftPos = {curPosition.getRow(), curPosition.getCol() - 1};
        if (board.isValidPos(leftPos) && board.isPositionOccupiedByColor(leftPos, ChessColor::BLACK)) {
            ChessPiece* cp = board.getCellAtPos(leftPos).getChessPiece();
            if (cp->getType() == ChessType::PAWN && cp->getTotalMoves() == 1) {
                Pawn* pawn = dynamic_cast<Pawn*>(cp);
                if (pawn->justMadeDoubleStep) {
                    ValidMove enPassantLeft {curPosition, {curPosition.getRow() + 1, curPosition.getCol() - 1},
                                             this, true, canCheck};
                    enPassantLeft.isEnPassant();
                    if (check) {
                        bool willCheck = board.simulateEnPassant(enPassantLeft, color);
                        if (!willCheck) {
                            moves.emplace_back(enPassantLeft);
                        }
                    } else moves.emplace_back(enPassantLeft);
                }
            }
        }

        // check right cell
        Position rightPos = {curPosition.getRow(), curPosition.getCol() + 1};
        if (board.isValidPos(rightPos) && board.isPositionOccupiedByColor(rightPos, ChessColor::BLACK)) {
            ChessPiece* cp = board.getCellAtPos(rightPos).getChessPiece();
            if (cp->getType() == ChessType::PAWN && cp->getTotalMoves() == 1) {
                Pawn* pawn = dynamic_cast<Pawn*>(cp);
                if (pawn->justMadeDoubleStep) {
                    ValidMove enPassantRight {curPosition, {curPosition.getRow() + 1, curPosition.getCol() + 1},
                                              this, true, canCheck};
                    enPassantRight.isEnPassant();
                    if (check) {
                        bool willCheck = board.simulateEnPassant(enPassantRight, color);
                        if (!willCheck) {
                            moves.emplace_back(enPassantRight);
                        }
                    } else moves.emplace_back(enPassantRight);
                }
            }
        }
    } else if (color == ChessColor::BLACK && curPosition.getRow() == 4) {
        // check left cell
        Position leftPos = {curPosition.getRow(), curPosition.getCol() - 1};
        if (board.isValidPos(leftPos) && board.isPositionOccupiedByColor(leftPos, ChessColor::WHITE)) {
            ChessPiece* cp = board.getCellAtPos(leftPos).getChessPiece();
            if (cp->getType() == ChessType::PAWN && cp->getTotalMoves() == 1) {
                Pawn* pawn = dynamic_cast<Pawn*>(cp);
                if (pawn->justMadeDoubleStep) {
                    ValidMove enPassantLeft {curPosition, {curPosition.getRow() - 1, curPosition.getCol() - 1},
                                             this, true, canCheck};
                    enPassantLeft.isEnPassant();
                    if (check) {
                        bool willCheck = board.simulateEnPassant(enPassantLeft, color);
                        if (!willCheck) {
                            moves.emplace_back(enPassantLeft);
                        }
                    } else moves.emplace_back(enPassantLeft);
                }
            }
        }

        // check right cell
        Position rightPos = {curPosition.getRow(), curPosition.getCol() + 1};
        if (board.isValidPos(rightPos) && board.isPositionOccupiedByColor(rightPos, ChessColor::WHITE)) {
            ChessPiece* cp = board.getCellAtPos(rightPos).getChessPiece();
            if (cp->getType() == ChessType::PAWN && cp->getTotalMoves() == 1) {
                Pawn* pawn = dynamic_cast<Pawn*>(cp);
                if (pawn->justMadeDoubleStep) {
                    ValidMove enPassantRight {curPosition, {curPosition.getRow() - 1, curPosition.getCol() + 1},
                                              this, true, canCheck};
                    enPassantRight.isEnPassant();
                    if (check) {
                        bool willCheck = board.simulateEnPassant(enPassantRight, color);
                        if (!willCheck) {
                            moves.emplace_back(enPassantRight);
                        }
                    } else moves.emplace_back(enPassantRight);
                }
            }
        }
    }

    return moves;
}

bool Pawn::checkPromotion(const Position& pos) {
    if (pos.getRow() == 8 && color == ChessColor::WHITE) {
        return true;
    }
    if (pos.getRow() == 1 && color == ChessColor::BLACK) {
        return true;
    }
    return false;
}

void Pawn::setJustMadeDoubleStep(bool flag) {
    justMadeDoubleStep = flag;
}

