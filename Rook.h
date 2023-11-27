#ifndef CHESS_ROOK_H
#define CHESS_ROOK_H
#include "ChessPiece.h"

class Rook : public ChessPiece {
    void addPossibleMoveByDirection(std::vector<ValidMove> possibleMoves,
                                    const Position& curPosition, int dx, int dy, int maxMoves);
    public:
        Rook(ChessBoard& board, Player& owner);
        bool isMovePossiblyValid(const Move& move)  override;
        std::vector<ValidMove> getAvailableMoves(const Position& curPosition)  override;
};


#endif //CHESS_ROOK_H
