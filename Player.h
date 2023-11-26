#ifndef CHESS_PLAYER_H
#define CHESS_PLAYER_H


#include "ChessBoard.h"

class Player {
    int playerNo;
    bool isComputer;
    const ChessColor& color;
    ChessBoard* board;
public:
    Player(int playerNo, bool isComputer, ChessBoard* board, const ChessColor& color);
    virtual bool makeMove(const Move& move) = 0;
};


#endif //CHESS_PLAYER_H
