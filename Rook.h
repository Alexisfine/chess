#ifndef CHESS_ROOK_H
#define CHESS_ROOK_H
#include "ChessPiece.h"

class Rook : public ChessPiece {
    public:
        Rook(ChessBoard& board, Player& owner);
        bool isMovePossiblyValid(const Move& move) const override;
        std::vector<Move> getAvailableMoves(const Position& curPosition) const override;
};


#endif //CHESS_ROOK_H
