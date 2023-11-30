#ifndef CHESS_ROOK_H
#define CHESS_ROOK_H
#include "ChessPiece.h"

class Rook : public ChessPiece {
    vector<ValidMove> addPossibleMoveByDirection(ChessBoard& board,
                                    const Position& curPosition, int dx, int dy, int maxMoves, bool check);
    public:
        Rook(ChessColor color);
        bool isMovePossiblyValid(ChessBoard& board, const Move& move)  override;
        std::vector<ValidMove> getAvailableMoves(ChessBoard& board, const Position& curPosition, bool check)  override;

};


#endif //CHESS_ROOK_H
