#include "Position.h"

Position::Position(int row, int col) : row{row}, col{col} {}
int Position::getRow() const {
    return row;
}
int Position::getCol() const {
    return col;
}
void Position::setRow(int newRow) {
    row = newRow;
}
void Position::setCol(int newCol) {
    col = newCol;
}

bool operator==(const Position& a, const Position& b) {
    return a.getRow() == b.getRow() && a.getCol() == b.getCol();
}
