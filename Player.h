#ifndef CHESS_PLAYER_H
#define CHESS_PLAYER_H


#include "ChessBoard.h"
#include "ChessPiece.h"
using namespace std;

enum class ChessColor;
class ChessPiece;
class ChessBoard;
class Move;

class Player {
protected:
    int playerNo;
    bool isComputer;
    const ChessColor color;
    ChessBoard* board;
public:
    Player(int playerNo, bool isComputer, ChessBoard* board, const ChessColor color);
    virtual ~Player();
    virtual bool makeMove(const Move& move) = 0;
    int getPlayerNo() const;
    virtual const ChessColor getColor() const;
};


#endif //CHESS_PLAYER_H
