#include "XWindow.h"
#include <iostream>

// Constructor
XWindow::XWindow(int width, int height) : width(width), height(height) {
    // Open display
    display = XOpenDisplay(NULL);
    if (!display) {
        std::cerr << "Error: Cannot open X display" << std::endl;
        exit(1);
    }
    
    // Create main window
    int screen = DefaultScreen(display);
    backgroundColor = WhitePixel(display, screen);
    textColor = BlackPixel(display, screen);
    borderColor = BlackPixel(display, screen);
    
    window = XCreateSimpleWindow(
        display, RootWindow(display, screen),
        0, 0, width, height, 2,
        borderColor, backgroundColor
    );
    
    // Create graphics context
    XGCValues values;
    gc = XCreateGC(display, window, 0, &values);
    XSetForeground(display, gc, textColor);
    XSetBackground(display, gc, backgroundColor);
    
    // Load font
    font = XLoadQueryFont(display, "9x15");
    if (font) {
        XSetFont(display, gc, font->fid);
    }
    
    // Setup input events
    selectInput(ExposureMask | ButtonPressMask | KeyPressMask | StructureNotifyMask);
}

// Destructor
XWindow::~XWindow() {
    if (font) {
        XFreeFont(display, font);
    }
    
    for (auto& button : buttons) {
        XDestroyWindow(display, button.win);
    }
    
    XFreeGC(display, gc);
    XDestroyWindow(display, window);
    XCloseDisplay(display);
}

// Window management
void XWindow::map() {
    XMapWindow(display, window);
}

void XWindow::unmap() {
    XUnmapWindow(display, window);
}

void XWindow::setTitle(const std::string& title) {
    XStoreName(display, window, title.c_str());
}

void XWindow::flush() {
    XFlush(display);
}

// Drawing methods
void XWindow::fillRectangle(int x, int y, int width, int height, unsigned long color) {
    XSetForeground(display, gc, color);
    XFillRectangle(display, window, gc, x, y, width, height);
}

void XWindow::drawRectangle(int x, int y, int width, int height, unsigned long color) {
    XSetForeground(display, gc, color);
    XDrawRectangle(display, window, gc, x, y, width, height);
}

void XWindow::drawLine(int x1, int y1, int x2, int y2, unsigned long color) {
    XSetForeground(display, gc, color);
    XDrawLine(display, window, gc, x1, y1, x2, y2);
}

void XWindow::drawString(int x, int y, const std::string& text) {
    XDrawString(display, window, gc, x, y, text.c_str(), text.length());
}

void XWindow::drawCenteredText(Window win, const std::string& text, int x, int y) {
    if (!font) return;
    
    int textWidth = XTextWidth(font, text.c_str(), text.length());
    int textX = x - textWidth / 2;
    
    XSetForeground(display, gc, textColor);
    XDrawString(display, win, gc, textX, y, text.c_str(), text.length());
}

// Color management
unsigned long XWindow::allocateColor(const std::string& colorName) {
    Colormap colormap = DefaultColormap(display, DefaultScreen(display));
    XColor xcolor;
    
    XParseColor(display, colormap, colorName.c_str(), &xcolor);
    XAllocColor(display, colormap, &xcolor);
    
    return xcolor.pixel;
}

void XWindow::setForeground(unsigned long color) {
    XSetForeground(display, gc, color);
}

void XWindow::setBackground(unsigned long color) {
    XSetBackground(display, gc, color);
}

// Button management
void XWindow::createButton(const std::string& label, int x, int y, int width, int height) {
    Button button;
    button.label = label;
    button.width = width;
    button.height = height;
    button.x = x;
    button.y = y;
    
    // Create button window
    button.win = XCreateSimpleWindow(
        display, window,
        x, y, width, height, 1,
        borderColor, backgroundColor
    );
    
    // Enable button events
    XSelectInput(display, button.win, ButtonPressMask | ExposureMask);
    
    // Map the button
    XMapWindow(display, button.win);
    
    // Draw button label
    drawCenteredText(button.win, label, width / 2, height / 2 + 5);
    
    buttons.push_back(button);
}

bool XWindow::isButtonClick(Window clickedWindow, int& buttonIndex) {
    for (size_t i = 0; i < buttons.size(); i++) {
        if (buttons[i].win == clickedWindow) {
            buttonIndex = i;
            return true;
        }
    }
    return false;
}

// Event handling
void XWindow::selectInput(long eventMask) {
    XSelectInput(display, window, eventMask);
}

bool XWindow::handleEvent(XEvent& event) {
    return XNextEvent(display, &event) == 0;
}

// Utility methods
void XWindow::clear() {
    XClearWindow(display, window);
}

void XWindow::drawGrid(int startX, int startY, int gridWidth, int gridHeight, int rows, int cols) {
    int cellWidth = gridWidth / cols;
    int cellHeight = gridHeight / rows;
    
    // Draw vertical lines
    for (int i = 0; i <= cols; i++) {
        drawLine(startX + i * cellWidth, startY,
                startX + i * cellWidth, startY + gridHeight,
                borderColor);
    }
    
    // Draw horizontal lines
    for (int i = 0; i <= rows; i++) {
        drawLine(startX, startY + i * cellHeight,
                startX + gridWidth, startY + i * cellHeight,
                borderColor);
    }
} 
