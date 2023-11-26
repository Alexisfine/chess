#include "Cell.h"

Cell::Cell(int row, int col) : row{row}, col{col}, state{CellState::EMPTY}, chessPiece{nullptr} {}

ChessPiece* Cell::getChessPiece() {
    return chessPiece;
}

bool Cell::isOccupied() {
    return state == CellState::OCCUPIED;
}

bool Cell::isOccupiedByMe(Player& player) {
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