#include "TwoPlayerChessBoard.h"

TwoPlayerChessBoard::TwoPlayerChessBoard(int dimension) : ChessBoard{dimension} {}
bool TwoPlayerChessBoard::makeMove(const Move& move) {
    if (!isMoveLegal(move)) return false;
}
bool TwoPlayerChessBoard::isMoveLegal(const Move& move) {
    return false;
}
bool TwoPlayerChessBoard::isValidPos(const Position& pos) {
    return pos.getRow() >= 0 && pos.getRow() < dimension && pos.getCol() >= 0 && pos.getCol() < dimension;
}