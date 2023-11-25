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
    PAWN
};

class ChessPiece {
    ChessType type;
    ChessBoard* board;
    Player* owner;
    Position position;
    bool alive;
public:
    ChessPiece(ChessType type, ChessBoard* board, Player* owner, int row, int col);
    bool isAlive();
    bool isMovePossiblyValid(Move move);
    std::vector<Move> getAvailableMoves();
    virtual ~ChessPiece() = 0;
};


#endif //CHESS_CHESSPIECE_H
