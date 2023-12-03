#ifndef CHESS_XDISPLAY_H
#define CHESS_XDISPLAY_H

class Cell;
enum class displayType {Text, Graphical};

class XDisplay {
    public:
        virtual displayType disType() = 0;
        virtual void notify(Cell &c) = 0;
        virtual ~XDisplay() = default;
};


#endif //CHESS_XDISPLAY_H
