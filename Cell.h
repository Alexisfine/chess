#ifndef CHESS_CELL_H
#define CHESS_CELL_H


#include "ChessPiece.h"

enum class CellState {
    OCCUPIED,
    EMPTY
};

class Cell {
    int row, col;
    CellState state;
    ChessPiece* chessPiece;
public:
    Cell(int row, int col);
    ChessPiece* getChessPiece() const;
    bool isOccupied() const;
    bool isOccupiedByMe(const Player& player) const;
    void addChessPiece(ChessPiece& newChessPiece);
    void removeChessPiece();
};

#endif //CHESS_CELL_H
