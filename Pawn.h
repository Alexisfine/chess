#ifndef CHESS_PAWN_H
#define CHESS_PAWN_H
#include "ChessPiece.h"

class Pawn : public ChessPiece {
    Pawn(ChessBoard& board, Player& player);
    bool isMovePossiblyValid(const Move& move) const override;
    std::vector<Move> getAvailableMoves(const Position& curPosition) const override;
};


#endif //CHESS_PAWN_H
