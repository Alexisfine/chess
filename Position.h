#ifndef CHESS_POSITION_H
#define CHESS_POSITION_H


class Position {
    int row, col;
public:
    Position(int row, int col);
    int getRow();
    int getCol();
    void setRow(int row);
    void setCol(int col);
};


#endif //CHESS_POSITION_H
