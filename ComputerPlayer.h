#ifndef CHESS_COMPUTERPLAYER_H
#define CHESS_COMPUTERPLAYER_H


#include "Player.h"

class ComputerPlayer : public Player {
    int level;
    public:
        ComputerPlayer(int playerNo, ChessBoard* board, const ChessColor& color);
        ChessColor getColor();
        bool oneMove();
        int randomint(int size);
};


#endif //CHESS_COMPUTERPLAYER_H
