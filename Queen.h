#ifndef CHESS_QUEEN_H
#define CHESS_QUEEN_H
#include "ChessPiece.h"

class Queen : public ChessPiece {
    bool block = false;
    vector<ValidMove> addPossibleMoveByDirection(ChessBoard& board,
                                    const Position& curPosition, int dx, int dy, int maxMoves, bool check);
    public:
        Queen(ChessColor color);
        MoveResult isMovePossiblyValid(ChessBoard& board, const Move& move) override;
        std::vector<ValidMove> getAvailableMoves(ChessBoard& board, const Position& curPosition, bool check) override;

};


#endif //CHESS_QUEEN_H

