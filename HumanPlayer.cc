#include "HumanPlayer.h"

HumanPlayer::HumanPlayer(int playerNo, ChessBoard *board, const ChessColor &color) :
    Player{playerNo, PlayerType::HUMAN, board, color} {}

