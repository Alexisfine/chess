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

class ChessPiece {
protected:
    ChessType type;
    ChessBoard& board;
    bool alive;
    Player& owner;
public:
    ChessPiece(ChessType type, ChessBoard& board, Player& owner);
    virtual ~ChessPiece();
    ChessType getType() const;
    Player& getOwner();
    bool isAlive() const;
    void changeAliveState();
    virtual bool isMovePossiblyValid(const Move& move) const = 0;
    virtual std::vector<ValidMove> getAvailableMoves(const Position& curPosition) = 0;
};

bool operator==(const ChessPiece& a, const ChessPiece& b);
#endif //CHESS_CHESSPIECE_H
