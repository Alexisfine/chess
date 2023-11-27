#include <iostream>
#include "TextDisplay.h"
#include "Cell.h"
using namespace std;

TextDisplay::TextDisplay(int n) : theDisplay(n), gridSize{n} { // Initialize theDisplay with size n
    theDisplay[0] = {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'};
    theDisplay[n - 1] = {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'};
    theDisplay[1] = std::vector<char>(8, 'p');
    theDisplay[n - 2] = std::vector<char>(8, 'P');
    for (int i = 2; i < n - 2; ++i) {
        theDisplay[i].resize(n); // Ensure each inner vector is of size n
        for (int j = 0; j < n; ++j) {
            if (i % 2 == j % 2) {
                theDisplay[i][j] = '_';
            } else {
                theDisplay[i][j] = ' ';
            }
        }
    }
}

displayType TextDisplay::disType() {
    return displayType::Text;
}

void TextDisplay::notify(Cell &c) {
    int row = c.getPosition()[0];
    int col = c.getPosition()[1];
    //if there is a chesspiece on the cell
    if (c.isOccupied()) {
        ChessPiece* myChessPiece = c.getChessPiece();
        char displayChar = ' ';
        switch (myChessPiece->getType()) {
            case ChessType::KING:
                displayChar = (myChessPiece->getColor() == ChessColor::WHITE) ? 'K' : 'k';
                break;
            case ChessType::QUEEN:
                displayChar = (myChessPiece->getColor() == ChessColor::WHITE) ? 'Q' : 'q';
                break;
            case ChessType::BISHOP:
                displayChar = (myChessPiece->getColor() == ChessColor::WHITE) ? 'B' : 'b';
                break;
            case ChessType::ROOK:
                displayChar = (myChessPiece->getColor() == ChessColor::WHITE) ? 'R' : 'r';
                break;
            case ChessType::KNIGHT:
                displayChar = (myChessPiece->getColor() == ChessColor::WHITE) ? 'N' : 'n';
                break;
            case ChessType::PAWN:
                displayChar = (myChessPiece->getColor() == ChessColor::WHITE) ? 'P' : 'p';
                break;
        }
        theDisplay[row][col] = displayChar;    
    }
    //if the cell is empty
    else if (row % 2 == col % 2) {
        theDisplay[row][col] = '_';
    } else {
        theDisplay[row][col] = ' ';
    }
}

TextDisplay::~TextDisplay() {}

ostream &operator<<(ostream &out, const TextDisplay &td) {
    int row = gridSize;
    for (int i = 0; i < td.gridSize; ++i) { // loop through TextDisplay (a 2D vector) 
        out << row << " "; // print the row number (starts at 8)
        row--;
        for (int j = 0; j < td.gridSize; ++j) {
            out << td.theDisplay[i][j]; // prints out cell (empty cell or a chesspiece)
        }
        out << endl;
    }
    out << endl;

    // print column letters (a,b,...,h)
    char ch = 'a';
    for (int i = 0; i < td.gridSize; ++i) {
        out << ch;
        ch++;
    }
    return out;
}
