#include "GraphicsDisplay.h"
#include <iostream>

using namespace std;

string mapChessPieceToChar(Cell& cell) {
    if (!cell.isOccupied()) return ""; // draw nothing if cell is empty
    string res;
    if (cell.isOccupiedByColor(ChessColor::WHITE)) {
        switch (cell.getChessPiece()->getType()) {
            case ChessType::KING:
                res = "K";
                break;
            case ChessType::QUEEN:
                res = "Q";
                break;
            case ChessType::ROOK:
                res = "R";
                break;
            case ChessType::BISHOP:
                res = "B";
                break;
            case ChessType::KNIGHT:
                res = "N";
                break;
            case ChessType::PAWN:
                res = "P";
                break;
        }
    } else {
        switch (cell.getChessPiece()->getType()) {
            case ChessType::KING:
                res = "k";
                break;
            case ChessType::QUEEN:
                res = "q";
                break;
            case ChessType::ROOK:
                res = "r";
                break;
            case ChessType::BISHOP:
                res = "b";
                break;
            case ChessType::KNIGHT:
                res = "n";
                break;
            case ChessType::PAWN:
                res = "p";
                break;
        }
    }

    return res;
}

// constructor
GraphicsDisplay::GraphicsDisplay(XWindow& xw, int gs) :
        xw{xw}, gridSize{gs + 1} {
    gridDisplay.resize(gridSize, vector<string>(gridSize, ""));
    drawGrid();
}

// notify to change state
void GraphicsDisplay::notify(Cell& c)  {
    int cellSize = windowSize / gridSize;
    int x = c.getPosition().getCol() * cellSize;
    int y = (gridSize - c.getPosition().getRow()) * cellSize;
    int row = gridSize - c.getPosition().getRow();
    int col = c.getPosition().getCol();
    int color = row % 2 != col % 2 ? XWindow::DarkRed : XWindow::Brown;
    xw.fillRectangle(x, y, cellSize, cellSize, color);
    gridDisplay[row][col] = mapChessPieceToChar(c);
    if (c.isOccupied()) {
        if (c.isOccupiedByColor(ChessColor::WHITE)) {
            xw.drawString(x + (cellSize / 3), y + (cellSize / 2), mapChessPieceToChar(c), XWindow::White);
        } else xw.drawString(x + (cellSize / 3), y + (cellSize / 2), mapChessPieceToChar(c), XWindow::Black);
    }
}

void GraphicsDisplay::drawGrid() {
    int cellSize = windowSize / gridSize;
    char col = 'a';
    string colStr;
    for (int i = 1; i <= gridSize; i++) {
        colStr = {col};
        xw.drawString(i*cellSize + cellSize/3, cellSize/2, colStr);
        col += 1;
    }
    for (int i = 1; i <= gridSize; i++) {
        xw.drawString(cellSize/3, i * cellSize + cellSize/2, to_string(gridSize-i));
        for (int j = 1; j < gridSize; j++) {
            if (i % 2 == j % 2) {
                xw.fillRectangle(j*cellSize, i*cellSize, cellSize, cellSize, XWindow::DarkRed);
            } else xw.fillRectangle(j*cellSize, i*cellSize, cellSize, cellSize, XWindow::Brown);
        }
    }
}

displayType GraphicsDisplay::disType() {
    return displayType::Graphical;
}


// destructor
GraphicsDisplay::~GraphicsDisplay() {
}
