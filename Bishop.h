#ifndef CHESS_BISHOP_H
#define CHESS_BISHOP_H
#include "ChessPiece.h"

class Bishop : public ChessPiece {
    void addPossibleMoveByDirection(std::vector<ValidMove> possibleMoves,
                                    const Position& curPosition, int dx, int dy, int maxMoves);
    public:
        Bishop(ChessBoard& board, Player& owner);
        bool isMovePossiblyValid(const Move& move) override;
        std::vector<ValidMove> getAvailableMoves(const Position& curPosition) override;
};


#endif //CHESS_BISHOP_H
