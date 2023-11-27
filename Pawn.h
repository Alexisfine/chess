#ifndef CHESS_PAWN_H
#define CHESS_PAWN_H
#include "ChessPiece.h"

class Pawn : public ChessPiece {
    int moveDx, moveDy;
public:
    Pawn(ChessBoard& board, Player& player);
    bool isMovePossiblyValid(const Move& move) override;
    std::vector<ValidMove> getAvailableMoves(const Position& curPosition) override;

};


#endif //CHESS_PAWN_H
