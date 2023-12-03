#ifndef CHESS_PAWN_H
#define CHESS_PAWN_H
#include "ChessPiece.h"

class Pawn : public ChessPiece {
    int moveDx, moveDy, capture1x, capture1y, capture2x, capture2y;
    bool justMadeDoubleStep;
    bool checkPromotion(const Position& pos);
public:
    Pawn(ChessColor color);
    MoveResult isMovePossiblyValid(ChessBoard& board, const Move& move) override;
    std::vector<ValidMove> getAvailableMoves(ChessBoard& board, const Position& curPosition, bool check) override;
    void setJustMadeDoubleStep(bool flag);


};


#endif //CHESS_PAWN_H
