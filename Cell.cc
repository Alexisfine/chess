#include "Cell.h"

Cell::Cell(int row, int col) : row{row}, col{col}, state{CellState::EMPTY}, chessPiece{nullptr} {}
Cell::Cell() {}
ChessPiece* Cell::getChessPiece() const {
    return chessPiece;
}

Position Cell::getPosition() const {
    Position p = {row, col};
    return p;
}

CellState Cell::getState() const{
    return state;
}

bool Cell::isOccupied() const {
    return state == CellState::OCCUPIED;
}

bool Cell::isOccupiedByColor(const ChessColor& color) const {
    if (state == CellState::EMPTY) return false;
    return chessPiece->getColor() == color;
}

void Cell::addChessPiece(ChessPiece* newChessPiece) {
    chessPiece = newChessPiece;
    state = CellState::OCCUPIED;
}

void Cell::removeChessPiece() {
    chessPiece = nullptr;
    state = CellState::EMPTY;
}

ostream& operator<<(ostream& out, const Cell& cell) {
    return out;
}
