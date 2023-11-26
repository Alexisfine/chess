#include "Move.h"

Move::Move(Position& start, Position& end, ChessPiece* chessPiece) :
    start{start},end{end}, chessPiece{chessPiece} {}
