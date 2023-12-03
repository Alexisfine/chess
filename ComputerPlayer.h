#ifndef CHESS_COMPUTERPLAYER_H
#define CHESS_COMPUTERPLAYER_H


#include "Player.h"

class ComputerPlayer : public Player {
    int level = 1;
    bool oneMove();
    public:
        ComputerPlayer(int playerNo, ChessBoard* board, const ChessColor& color);
        void setLevel(int newLevel);
        const ChessColor getColor() const override;
        int randomint(int size);
        ValidMove getMove();
};


#endif //CHESS_COMPUTERPLAYER_H
