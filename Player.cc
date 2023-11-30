#include "Player.h"


Player::Player(int playerNo, PlayerType playerType, ChessBoard* board, const ChessColor color) :
    playerNo{playerNo}, playerType{playerType}, board{board}, color{color} {}

int Player::getPlayerNo() const {
    return playerNo;
}
const ChessColor Player::getColor() const{
    return color;
}

Player::~Player() {}

PlayerType Player::getPlayerType() {
    return playerType;
}




