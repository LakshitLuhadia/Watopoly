#ifndef XWINDOW_H
#define XWINDOW_H

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysymdef.h>
#include <string>
#include <vector>

class XWindow {
    Display* display;
    Window window;
    GC gc;
    XFontStruct* font;
    int width, height;
    unsigned long backgroundColor;
    unsigned long textColor;
    unsigned long borderColor;
    
    // Button management
    struct Button {
        Window win;
        std::string label;
        int x, y, width, height;
    };
    std::vector<Button> buttons;
    
public:
    // Constructor and destructor
    XWindow(int width = 800, int height = 800);
    ~XWindow();
    
    // Window management
    void map();
    void unmap();
    void setTitle(const std::string& title);
    void flush();
    
    // Drawing methods
    void fillRectangle(int x, int y, int width, int height, unsigned long color);
    void drawRectangle(int x, int y, int width, int height, unsigned long color);
    void drawLine(int x1, int y1, int x2, int y2, unsigned long color);
    void drawString(int x, int y, const std::string& text);
    void drawCenteredText(Window win, const std::string& text, int x, int y);
    
    // Color management
    unsigned long allocateColor(const std::string& colorName);
    void setForeground(unsigned long color);
    void setBackground(unsigned long color);
    
    // Button management
    void createButton(const std::string& label, int x, int y, int width, int height);
    bool isButtonClick(Window clickedWindow, int& buttonIndex);
    
    // Event handling
    void selectInput(long eventMask);
    bool handleEvent(XEvent& event);
    
    // Getters
    Display* getDisplay() const { return display; }
    Window getWindow() const { return window; }
    GC getGC() const { return gc; }
    XFontStruct* getFont() const { return font; }
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    unsigned long getBackgroundColor() const { return backgroundColor; }
    unsigned long getTextColor() const { return textColor; }
    unsigned long getBorderColor() const { return borderColor; }
    
    // Utility methods
    void clear();
    void drawGrid(int startX, int startY, int gridWidth, int gridHeight, int rows, int cols);
};

#endif 
