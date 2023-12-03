#ifndef CHESS_VALIDMOVE_H
#define CHESS_VALIDMOVE_H


#include "Move.h"
class ChessPiece;
class ValidMove : public Move {
    bool canCapture;
    bool canCheck;
    bool enPassant;
    bool promotion;
public:
    ValidMove(Position start, Position end, ChessPiece* chessPiece, bool canCapture, bool canCheck);
    bool operator<(const ValidMove& other) const;
    Position getStart() const;
    Position getEnd() const;
    void isEnPassant();
    bool getEnPassant() const;
    void setPromotion(bool p);
    bool getPromotion();
};


#endif //CHESS_VALIDMOVE_H
