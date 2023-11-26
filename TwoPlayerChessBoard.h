#ifndef CHESS_TWOPLAYERCHESSBOARD_H
#define CHESS_TWOPLAYERCHESSBOARD_H


#include "ChessBoard.h"

class TwoPlayerChessBoard : public ChessBoard {
public:
    TwoPlayerChessBoard(int dimension);
    bool makeMove(const Move& move, const Player& player) override;
    bool isMoveLegal(const Move& move, const Player& player) const override;
    bool isValidPos(const Position& pos) const override;
};


#endif //CHESS_TWOPLAYERCHESSBOARD_H
