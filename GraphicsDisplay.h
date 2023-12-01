#ifndef CHESS_GRAPHICSDISPLAY_H
#define CHESS_GRAPHICSDISPLAY_H

#include <vector>
#include "XDisplay.h"
#include "XWindow.h"
using namespace std;

class GraphicsDisplay : public XDisplay {
    int gridSize;
    vector<vector<char>> gridDisplay;
    XWindow& xw;
};


#endif //CHESS_GRAPHICSDISPLAY_H
