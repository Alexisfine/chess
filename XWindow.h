#ifndef CHESS_XWINDOW_H
#define CHESS_XWINDOW_H
#include <X11/Xlib.h>
#include <iostream>
#include <string>
#include "XDisplay.h"

class XWindow {
    Display *d;
    Window w;
    int s;
    GC gc;
    unsigned long colours[10];
    int width, height;
public:
    XWindow(int width=500, int height=500);  // Constructor; displays the window.
    ~XWindow();                              // Destructor; destroys the window.

    enum {White=0, Black, Red, Green, Blue, Brown, DarkRed}; // Available colours.

    // Draws a rectangle
    void fillRectangle(int x, int y, int width, int height, int colour=Black);

    // Draws a string
    void drawString(int x, int y, std::string msg, int colour=Black);
    void setFont(const std::string& fontname);

};


#endif //CHESS_XWINDOW_H
