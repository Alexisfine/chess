#ifndef CHESS_DISPLAY_H
#define CHESS_DISPLAY_H

class Cell;
enum class displayType {Text, Graphical};

class Display {
    public:
        virtual displayType disType() = 0;
        virtual void notify(Cell &c) = 0;
        virtual ~Display() = default;
};


#endif //CHESS_DISPLAY_H
