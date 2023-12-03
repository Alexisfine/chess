#ifndef CHESS_GRAPHICSDISPLAY_H
#define CHESS_GRAPHICSDISPLAY_H

#include <vector>
#include "XDisplay.h"
#include "XWindow.h"
#include "Cell.h"
using namespace std;

class GraphicsDisplay : public XDisplay {
    int gridSize;
    vector<vector<string>> gridDisplay;
    const int windowSize = 500;
    XWindow& xw;
    void drawGrid();
public:
    GraphicsDisplay(XWindow& xw, int gridSize);
    displayType disType() override;
    void notify(Cell &c) override;
    ~GraphicsDisplay() override;
};


#endif //CHESS_GRAPHICSDISPLAY_H
