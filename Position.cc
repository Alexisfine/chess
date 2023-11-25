#include "Position.h"

Position::Position(int row, int col) : row{row}, col{col} {}
int Position::getRow() {
    return row;
}
int Position::getCol() {
    return col;
}
void Position::setRow(int newRow) {
    row = newRow;
}
void Position::setCol(int newCol) {
    col = newCol;
}
