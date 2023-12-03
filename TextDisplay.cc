#include <iostream>
#include "TextDisplay.h"
#include "Cell.h"
using namespace std;

TextDisplay::TextDisplay(int n) : theDisplay(n+1), gridSize{n} { // Initialize theDisplay with size n
//    theDisplay[1] = {'_','R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'};
//    theDisplay[n] = {'_','r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'};
//    theDisplay[2] = std::vector<char>(9, 'P');
//    theDisplay[n - 2] = std::vector<char>(9, 'p');

    for (int i = 0; i <= n; ++i) {
        theDisplay[i].resize(n+1); // Ensure each inner vector is of size n
        for (int j = 1; j <= n; ++j) {
            if ((i % 2 == j % 2) || ((i % 2 == 1) && (j % 2 == 1))) {
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
    int row = c.getPosition().getRow();
    int col = c.getPosition().getCol();
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
    else if ((row % 2 == col % 2) || (row % 2 == 1 && col % 2 == 1)) {
        theDisplay[row][col] = '_';
    } else {
        theDisplay[row][col] = ' ';
    }
}

TextDisplay::~TextDisplay() {}

std::ostream &operator<<(std::ostream &out, const TextDisplay &td) {
    for (int i = td.gridSize; i > 0; --i) { // loop through TextDisplay (a 2D vector)
        out << i << " "; // print the row number (starts at 1)
        for (int j = 1; j <= td.gridSize; ++j) {
            out << td.theDisplay[i][j]; // prints out cell (empty cell or a chesspiece)
        }
        out << endl;
    }
    out << endl;

    // print column letters (a,b,...,h)
    char ch = 'a';
    out << "  ";
    for (int i = 0; i < td.gridSize; ++i) {
        out << ch;
        ch++;
    }
    return out;
}
