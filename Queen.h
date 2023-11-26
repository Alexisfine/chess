#ifndef CHESS_QUEEN_H
#define CHESS_QUEEN_H
#include "ChessPiece.h"

class Queen : public ChessPiece {
    bool block = false;
    public:
        Queen(ChessBoard& board, Player& owner);
        bool isMovePossiblyValid(const Move& move) const override;
        std::vector<Move> getAvailableMoves(const Position& curPosition) const override;
};


#endif //CHESS_QUEEN_H

