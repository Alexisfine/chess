#ifndef CHESS_KNIGHT_H
#define CHESS_KNIGHT_H
#include "ChessPiece.h"

class Knight : public ChessPiece {
    public:
        Knight(ChessColor color);
        bool isMovePossiblyValid(ChessBoard& board, const Move& move) override;
        std::vector<ValidMove> getAvailableMoves(ChessBoard& board, const Position& curPosition, bool check) override;

};


#endif //CHESS_KNIGHT_H
