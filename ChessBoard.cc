#include "ChessBoard.h"

ChessBoard::ChessBoard(int dimension) : dimension{dimension}, board(dimension, std::vector<Cell>(dimension)){}
const Cell& ChessBoard::getCellAtPos(const Position& pos) const {
    return board[pos.getRow()][pos.getCol()];
}
void ChessBoard::setPieceAtPosition(const Position& pos, ChessPiece& piece) {
    board[pos.getRow()][pos.getCol()].addChessPiece(piece);
}

bool ChessBoard::isPositionEmpty(const Position& pos) const {
    return !board[pos.getRow()][pos.getCol()].isOccupied();
}

bool ChessBoard::isPositionOccupiedByPlayer(const Position& pos, const Player& player) const {
    return board[pos.getRow()][pos.getCol()].isOccupiedByMe(player);
}
