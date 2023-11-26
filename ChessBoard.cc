#include "ChessBoard.h"

ChessPiece* ChessBoard::getPieceAtPosition(Position& pos) {
    return board[pos.getRow()][pos.getCol()].getChessPiece();
}
void ChessBoard::setPieceAtPosition(Position& pos, ChessPiece& piece) {
    board[pos.getRow()][pos.getCol()].addChessPiece(piece);
}

bool ChessBoard::isPositionEmpty(Position& pos) {
    return !board[pos.getRow()][pos.getCol()].isOccupied();
}
