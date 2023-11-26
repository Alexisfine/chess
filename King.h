#ifndef CHESS_KING_H
#define CHESS_KING_H

#include "ChessPiece.h"

class King : public ChessPiece {
public:
    King(ChessBoard& board, Player& owner);
    bool isMovePossiblyValid(Move& move) const override;
    std::vector<Move> getAvailableMoves(Position& curPosition) override;
};


#endif //CHESS_KING_H
