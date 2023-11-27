#include "HumanPlayer.h"

HumanPlayer::HumanPlayer(int playerNo, ChessBoard *board, const ChessColor &color) :
    Player{playerNo, false, board, color} {}

bool HumanPlayer::makeMove(const Move& move) {
    return board->makeMove(move, *this);
}