#ifndef CHESS_CHESSPIECE_H
#define CHESS_CHESSPIECE_H

#include "ChessBoard.h"
#include "Position.h"
#include "Player.h"
#include "Move.h"
#include <vector>

enum class ChessType {
    KING,
    QUEEN,
    BISHOP,
    ROOK,
    KNIGHT,
    PAWN,
    EMPTY
};

class ChessPiece {
    ChessType type;
    ChessBoard* board;
    Player* owner;
    bool alive;
public:
    ChessPiece(ChessType type, ChessBoard* board, Player* owner);
    ChessType getType();
    bool isAlive();
    bool isMovePossiblyValid(Move move);
    std::vector<Move> getAvailableMoves();
    virtual ~ChessPiece() = 0;
};


#endif //CHESS_CHESSPIECE_H
