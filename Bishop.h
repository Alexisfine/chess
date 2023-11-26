#ifndef CHESS_BISHOP_H
#define CHESS_BISHOP_H
#include "ChessPiece.h"

class Bishop : public ChessPiece{
    public:
        Bishop(ChessBoard& board, Player& owner);
        bool isMovePossiblyValid(const Move& move) const override;
        std::vector<Move> getAvailableMoves(const Position& curPosition) const override;
};


#endif //CHESS_BISHOP_H
