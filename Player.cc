#include "Player.h"

Player::Player(int playerNo, bool isComputer, ChessBoard* board, const ChessColor& color) :
    playerNo{playerNo}, isComputer{isComputer}, board{board}, color{color} {}

int Player::getPlayerNo() const {
    return playerNo;
}