#include "ChessBoard.h"

ChessBoard::ChessBoard(int dimension) : dimension{dimension}, board(dimension, std::vector<Cell>(dimension)){}
ChessPiece* ChessBoard::getPieceAtPosition(const Position& pos) {
    return board[pos.getRow()][pos.getCol()].getChessPiece();
}
void ChessBoard::setPieceAtPosition(const Position& pos, ChessPiece& piece) {
    board[pos.getRow()][pos.getCol()].addChessPiece(piece);
}

bool ChessBoard::isPositionEmpty(const Position& pos) {
    return !board[pos.getRow()][pos.getCol()].isOccupied();
}
