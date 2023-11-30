
#ifndef CHESS_CHESSBOARD_H
#define CHESS_CHESSBOARD_H

#include <vector>
#include "Cell.h"
#include "TextDisplay.h"

class Move;
class Position;
class ChessPiece;
enum class ChessColor;
enum class ChessType;
class ValidMove;

class ChessBoard {
protected:
    int dimension;
    std::vector<std::vector<Cell>> board;
    TextDisplay textDisplay;
    std::vector<ChessPiece*> chessPieces;
public:
    ChessBoard(int dimension);
    virtual ~ChessBoard();
    virtual bool makeMove(Move move, ChessColor color) = 0;
    virtual bool isMoveLegal(const Move& move, ChessColor color) = 0;
    virtual bool isValidPos(const Position& pos) const = 0;
    bool isPositionEmpty(const Position& pos) const;
    bool isPositionOccupiedByColor(const Position& pos, const ChessColor& color) const;
    const Cell& getCellAtPos(const Position& pos) const;
    void setPieceAtPosition(const Position& pos, ChessPiece& piece);
    int getDimension() const;
    virtual void refresh() = 0;
    virtual bool isColorInCheck(ChessColor color) = 0;
    virtual bool isColorInCheckMate(ChessColor color) = 0;
    virtual void addTo(const Position& pos, ChessColor color, ChessType chessType) = 0;
    virtual void remove(const Position& pos) = 0;
    virtual bool verifySetup() = 0;
    virtual bool simulateMove(Move move, ChessColor color) = 0;
    virtual std::vector<ValidMove> getAllValidMoves(ChessColor color, bool check) = 0;
    friend std::ostream &operator<<(std::ostream &out, const ChessBoard& board);
};

#endif //CHESS_CHESSBOARD_H
