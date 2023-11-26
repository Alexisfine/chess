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
    Player& getOwner() const;
    bool isAlive() const;
    void changeAliveState();
    virtual bool isMovePossiblyValid(Move& move) const = 0;
    virtual std::vector<Move> getAvailableMoves(Position& curPosition) = 0;
};

#endif //CHESS_CHESSPIECE_H
