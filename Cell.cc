#include "Cell.h"

Cell::Cell(int row, int col) : row{row}, col{col}, state{CellState::EMPTY}, chessPiece{nullptr} {}

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

bool Cell::isOccupiedByMe(const Player& player) const {
    if (state == CellState::EMPTY) return false;
    return &chessPiece->getOwner() == &player;
}

void Cell::addChessPiece(ChessPiece& newChessPiece) {
    chessPiece = &newChessPiece;
    state = CellState::OCCUPIED;
}

void Cell::removeChessPiece() {
    chessPiece = nullptr;
    state = CellState::EMPTY;
}