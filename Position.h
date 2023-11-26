#ifndef CHESS_POSITION_H
#define CHESS_POSITION_H


class Position {
    int row, col;
public:
    Position(int row, int col);
    int getRow() const;
    int getCol() const;
    void setRow(int row);
    void setCol(int col);
};
bool operator==(const Position& a, const Position& b);

#endif //CHESS_POSITION_H
