#ifndef CHESS_PLAYER_H
#define CHESS_PLAYER_H


#include "ChessBoard.h"

class Player {
    int playerNo;
    bool isComputer;
    ChessBoard* board;
public:
    Player(int playerNo, bool isComputer, ChessBoard* board);
    virtual bool makeMove(const Move& move) = 0;
};


#endif //CHESS_PLAYER_H
