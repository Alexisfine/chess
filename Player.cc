#include "Player.h"

Player::Player(int playerNo, bool isComputer, ChessBoard* board) :
    playerNo{playerNo}, isComputer{isComputer}, board{board} {}
