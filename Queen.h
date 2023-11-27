#ifndef CHESS_QUEEN_H
#define CHESS_QUEEN_H
#include "ChessPiece.h"

class Queen : public ChessPiece {
    bool block = false;
    void addPossibleMoveByDirection(std::vector<ValidMove> possibleMoves,
                                    const Position& curPosition, int dx, int dy, int maxMoves);
    public:
        Queen(ChessBoard& board, Player& owner);
        bool isMovePossiblyValid(const Move& move) override;
        std::vector<ValidMove> getAvailableMoves(const Position& curPosition) override;
};


#endif //CHESS_QUEEN_H

