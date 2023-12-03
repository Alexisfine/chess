#ifndef CHESS_PLAYER_H
#define CHESS_PLAYER_H


#include "ChessBoard.h"
#include "ChessPiece.h"
using namespace std;

enum class ChessColor;
class ChessPiece;
class ChessBoard;
class Move;

enum class PlayerType {
    COMPUTER,
    HUMAN
};

class Player {
protected:
    int playerNo;
    PlayerType playerType;
    const ChessColor color;
    ChessBoard* board;
public:
    Player(int playerNo, PlayerType playerType, ChessBoard* board, const ChessColor color);
    virtual ~Player();
    int getPlayerNo() const;
    virtual const ChessColor getColor() const;
    PlayerType getPlayerType();
};


#endif //CHESS_PLAYER_H
