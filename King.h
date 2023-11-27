#ifndef CHESS_KING_H
#define CHESS_KING_H

#include "ChessPiece.h"
class King : public ChessPiece {
public:
    King(ChessBoard& board, Player& player);
    bool isMovePossiblyValid(const Move& move) override;
    std::vector<ValidMove> getAvailableMoves(const Position& curPosition) override;
};


#endif //CHESS_KING_H
