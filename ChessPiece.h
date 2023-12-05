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
struct MoveResult {
    bool success;
    bool pawnPromotion;
};


class ChessBoard;
class Player;

class ChessPiece {
protected:
    ChessType type;
    ChessColor color;
    int totalMoves = 0;
public:
    ChessPiece(ChessType type, ChessColor color);
    virtual ~ChessPiece();
    ChessType getType() const;
    ChessColor getColor() const;
    void incrementTotalMoves();
    virtual MoveResult isMovePossiblyValid(ChessBoard& board, const Move& move) = 0;
    virtual std::vector<ValidMove> getAvailableMoves(ChessBoard& board, const Position& curPosition, bool check) = 0;
    int getTotalMoves() const;
    int getScore() const;
};

bool operator==(const ChessPiece& a, const ChessPiece& b);
#endif //CHESS_CHESSPIECE_H
