#ifndef CHESS_CELL_H
#define CHESS_CELL_H


#include "ChessPiece.h"
#include <iostream>
class ChessPiece;
enum class ChessColor;
class Position;

enum class CellState {
    OCCUPIED,
    EMPTY
};

class Cell {
    int row, col;
    CellState state;
    ChessPiece* chessPiece;
public:
    Cell();
    Cell(int row, int col);
    ChessPiece* getChessPiece() const;
    Position getPosition() const;
    CellState getState() const;
    bool isOccupied() const;
    bool isOccupiedByColor(const ChessColor& color) const;
    void addChessPiece(ChessPiece* newChessPiece);
    void removeChessPiece();
};

std::ostream& operator<<(std::ostream& out, const Cell& cell);

#endif //CHESS_CELL_H
