#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include "XWindow.h"

using namespace std;

XWindow::XWindow(int width, int height) {

    d = XOpenDisplay(NULL);
    if (d == NULL) {
        cerr << "Cannot open display" << endl;
        exit(1);
    }
    s = DefaultScreen(d);
    w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, width, height, 1,
                            BlackPixel(d, s), WhitePixel(d, s));
    XSelectInput(d, w, ExposureMask | KeyPressMask);
    XMapRaised(d, w);

    Pixmap pix = XCreatePixmap(d,w,width,
                               height,DefaultDepth(d,DefaultScreen(d)));
    gc = XCreateGC(d, pix, 0,(XGCValues *)0);

    XFlush(d);
    XFlush(d);

    setFont("lucidasanstypewriter-bold-24");


    // Set up colours.
    XColor xcolour;
    Colormap cmap;
    char color_vals[7][12]={"white", "black", "red", "green", "blue", "#C89C78", "#6E042C"};

    cmap=DefaultColormap(d,DefaultScreen(d));
    for(int i=0; i < 7; ++i) {
        XParseColor(d,cmap,color_vals[i],&xcolour);
        XAllocColor(d,cmap,&xcolour);
        colours[i]=xcolour.pixel;
    }

    XSetForeground(d,gc,colours[Black]);

    // Make window non-resizeable.
    XSizeHints hints;
    hints.flags = (USPosition | PSize | PMinSize | PMaxSize );
    hints.height = hints.base_height = hints.min_height = hints.max_height = height;
    hints.width = hints.base_width = hints.min_width = hints.max_width = width;
    XSetNormalHints(d, w, &hints);

    XSynchronize(d,True);

    usleep(1000);
}

XWindow::~XWindow() {
    XFreeGC(d, gc);
    XCloseDisplay(d);

}

void XWindow::fillRectangle(int x, int y, int width, int height, int colour) {
    XSetForeground(d, gc, colours[colour]);
    XFillRectangle(d, w, gc, x, y, width, height);
    XSetForeground(d, gc, colours[Black]);
}

void XWindow::drawString(int x, int y, string msg, int colour) {
    XSetForeground(d, gc, colours[colour]);
    XDrawString(d, w, gc, x, y, msg.c_str(), msg.length());
    XSetForeground(d, gc, colours[Black]);

}

void XWindow::setFont(const std::string& fontname) {
    XFontStruct* font = XLoadQueryFont(d, fontname.c_str());
    if (!font) {
        std::cerr << "Font not found: " << fontname << std::endl;
        exit(1);
    }
    XSetFont(d, gc, font->fid);
}


