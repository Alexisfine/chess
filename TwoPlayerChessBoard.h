#ifndef CHESS_TWOPLAYERCHESSBOARD_H
#define CHESS_TWOPLAYERCHESSBOARD_H


#include "ChessBoard.h"

class TwoPlayerChessBoard : public ChessBoard {
public:
    TwoPlayerChessBoard(int dimension);
    bool makeMove(const Move& move) override;
    bool isMoveLegal(const Move& move) override;
    bool isValidPos(const Position& pos) override;
};


#endif //CHESS_TWOPLAYERCHESSBOARD_H
