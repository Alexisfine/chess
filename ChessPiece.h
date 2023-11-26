#ifndef CHESS_CHESSPIECE_H
#define CHESS_CHESSPIECE_H

#include "ChessBoard.h"
#include "Position.h"
#include "Player.h"
#include "Move.h"
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

class ChessPiece {
protected:
    ChessType type;
    ChessBoard& board;
    Player& owner;
    bool alive;
public:
    ChessPiece(ChessType type, ChessBoard& board, Player& owner);
    virtual ~ChessPiece();
    ChessType getType() const;
    Player& getOwner();
    bool isAlive() const;
    void changeAliveState();
    virtual bool isMovePossiblyValid(const Move& move) const = 0;
    virtual std::vector<Move> getAvailableMoves(const Position& curPosition) const = 0;
};

bool operator==(const ChessPiece& a, const ChessPiece& b);
#endif //CHESS_CHESSPIECE_H
