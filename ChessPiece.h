#ifndef CHESS_CHESSPIECE_H
#define CHESS_CHESSPIECE_H

#include "ChessBoard.h"
#include "Position.h"
#include "Player.h"
#include "Move.h"
#include "ValidMove.h"
#include <vector>
#include <memory>

enum class ChessType {
    KING,
    QUEEN,
    BISHOP,
    ROOK,
    KNIGHT,
    PAWN
};

enum class ChessColor {
    WHITE,
    BLACK,
    RED,
    BLUE
};

class ChessBoard;
class Player;

class ChessPiece {
protected:
    ChessType type;
    bool used;
    ChessColor color;
    bool firstMove;
public:
    ChessPiece(ChessType type, ChessColor color);
    virtual ~ChessPiece();
    ChessType getType() const;
    ChessColor getColor() const;
    bool isUsed() const;
    void setUsed(bool setUsed);
    void setFirstMoveToFalse();
    virtual bool isMovePossiblyValid(ChessBoard& board, const Move& move) = 0;
    virtual std::vector<ValidMove> getAvailableMoves(ChessBoard& board, const Position& curPosition, bool check) = 0;

};

bool operator==(const ChessPiece& a, const ChessPiece& b);
#endif //CHESS_CHESSPIECE_H
