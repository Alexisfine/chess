#ifndef CHESS_VALIDMOVE_H
#define CHESS_VALIDMOVE_H


#include "Move.h"

class ValidMove : public Move {
    bool canCapture;
    bool canCheck;
public:
    ValidMove(Position start, Position end, ChessPiece* chessPiece, bool canCapture, bool canCheck);
    bool operator<(const ValidMove& other) const;
    Position getStart() const;
    Position getEnd() const;
};


#endif //CHESS_VALIDMOVE_H
