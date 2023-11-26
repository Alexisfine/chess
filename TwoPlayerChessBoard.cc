#include "TwoPlayerChessBoard.h"

TwoPlayerChessBoard::TwoPlayerChessBoard(int dimension) : ChessBoard{dimension} {}
bool TwoPlayerChessBoard::makeMove(const Move& move, const Player& player) {
    // check if move is legal
    if (!isMoveLegal(move, player)) return false;

    // if new position contains a chess from the opponent, remove it
    if (!isPositionEmpty(move.getEnd()) && isPositionOccupiedByPlayer(move.getEnd(),player)) return false;

    // capture this chess
    ChessPiece* capturedChess = getCellAtPos(move.getEnd()).getChessPiece();
    if (capturedChess) {
        removePieceAtPosition(move.getEnd());
        capturedChess->changeAliveState();
    }

    // move chess to new position
    setPieceAtPosition(move.getEnd(), move.getChessPiece());
    removePieceAtPosition(move.getStart());

    return true;
}

bool TwoPlayerChessBoard::isMoveLegal(const Move& move, const Player& player) const {
    // check if the starting and ending position are valid
    if (!isValidPos(move.getStart()) || !isValidPos(move.getEnd())) return false;
    // check if the player has a chess at the starting position
    const Cell& cell = getCellAtPos(move.getStart());
    if (!cell.isOccupiedByMe(player)) return false;
    ChessPiece* chessPiece = cell.getChessPiece();
    return chessPiece->isMovePossiblyValid(move);
}

bool TwoPlayerChessBoard::isValidPos(const Position& pos) const {
    return pos.getRow() >= 0 && pos.getRow() < dimension && pos.getCol() >= 0 && pos.getCol() < dimension;
}