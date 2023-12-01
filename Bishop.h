#ifndef CHESS_BISHOP_H
#define CHESS_BISHOP_H
#include "ChessPiece.h"

class Bishop : public ChessPiece {
    std::vector<ValidMove> addPossibleMoveByDirection(ChessBoard& board,
                                    const Position& curPosition, int dx, int dy, int maxMoves, bool check);
    public:
        Bishop(ChessColor color);
        MoveResult isMovePossiblyValid(ChessBoard& board, const Move& move) override;
        std::vector<ValidMove> getAvailableMoves(ChessBoard& board, const Position& curPosition, bool check) override;

};


#endif //CHESS_BISHOP_H
