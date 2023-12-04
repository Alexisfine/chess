#ifndef CHESS_VALIDMOVE_H
#define CHESS_VALIDMOVE_H


#include "Move.h"
class ChessPiece;
class ValidMove : public Move {
    bool canCapture;
    bool canCheck;
    bool enPassant;
    bool promotion;
    int capturedScore;
    int beCapturedScore;
public:
    ValidMove(Position start, Position end, ChessPiece* chessPiece, bool canCapture, bool canCheck,
              int capturedScore, int beCapturedScore);
    bool operator<(const ValidMove& other) const;
    Position getStart() const;
    Position getEnd() const;
    void isEnPassant();
    bool getEnPassant() const;
    void setPromotion(bool p);
    bool getPromotion();
    bool getCanCapture() const;
    bool getCanCheck() const;
    int getCapturedScore() const;
    int getBeCapturedScore() const;
};


#endif //CHESS_VALIDMOVE_H
