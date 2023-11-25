#include "ChessBoard.h"

ChessType ChessBoard::getPieceAtPosition(Position pos) {
    return board[pos.getRow()][pos.getCol()].getChessType();
}
void ChessBoard::setPieceAtPosition(Position pos, ChessPiece* piece) {
    board[pos.getRow()][pos.getCol()].changeState(piece->getType(), piece);
}
