#ifndef CHESS_PAWN_H
#define CHESS_PAWN_H
#include "ChessPiece.h"

class Pawn : public ChessPiece {
    int moveDx, moveDy, capture1x, capture1y, capture2x, capture2y;
public:
    Pawn(ChessColor color);
    bool isMovePossiblyValid(ChessBoard& board, const Move& move) override;
    std::vector<ValidMove> getAvailableMoves(ChessBoard& board, const Position& curPosition, bool check) override;


};


#endif //CHESS_PAWN_H
