#ifndef CHESS_KING_H
#define CHESS_KING_H

#include "ChessPiece.h"
class King : public ChessPiece {
public:
    King(ChessColor color);
    MoveResult isMovePossiblyValid(ChessBoard& board, const Move& move) override;
    std::vector<ValidMove> getAvailableMoves(ChessBoard& board, const Position& curPosition, bool check) override;

};


#endif //CHESS_KING_H
