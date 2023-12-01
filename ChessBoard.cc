#include "ChessBoard.h"

ChessBoard::ChessBoard(int dimension) : dimension{dimension}, 
board(dimension + 1, std::vector<Cell>(dimension + 1)), textDisplay{dimension}{
    for (int row = 0; row <= dimension; row++) {
        for (int col = 0; col <= dimension; col++) {
            board[row][col] = {row, col};
        }
    }
}
const Cell& ChessBoard::getCellAtPos(const Position& pos) const {
    return board[pos.getRow()][pos.getCol()];
}

void ChessBoard::remove(const Position& pos) {
    board[pos.getRow()][pos.getCol()].removeChessPiece();
}

bool ChessBoard::isPositionEmpty(const Position& pos) const {
    return !board[pos.getRow()][pos.getCol()].isOccupied();
}

bool ChessBoard::isPositionOccupiedByColor(const Position& pos, const ChessColor& color) const {
    return board[pos.getRow()][pos.getCol()].isOccupiedByColor(color);
}

int ChessBoard::getDimension() const {
    return dimension;
}

ChessBoard::~ChessBoard() {}

std::ostream &operator<<(std::ostream &out, const ChessBoard& board) {
    out << board.textDisplay;
    return out;
}

void ChessBoard::completeSetup() {
    for (int row = 1; row <= dimension; row++) {
        for (int col = 1; col <= dimension; col++) {
            if (board[row][col].isOccupied()) {
                board[row][col].getChessPiece()->incrementTotalMoves();
            }
        }
    }
}