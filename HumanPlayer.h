#ifndef CHESS_HUMANPLAYER_H
#define CHESS_HUMANPLAYER_H


#include "Player.h"

class HumanPlayer : public Player {
public:
    HumanPlayer(int playerNo, ChessBoard* board, const ChessColor& color);
};


#endif //CHESS_HUMANPLAYER_H
