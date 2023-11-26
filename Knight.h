#ifndef CHESS_KNIGHT_H
#define CHESS_KNIGHT_H
#include "ChessPiece.h"

class Knight : public ChessPiece {
    public:
        Knight(ChessBoard& board, Player& owner);
        bool isMovePossiblyValid(const Move& move) const override;
        std::vector<Move> getAvailableMoves(const Position& curPosition) const override;
};


#endif //CHESS_KNIGHT_H
