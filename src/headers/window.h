#ifndef WINDOW_HEADER
#define WINDOW_HEADER
#include "/usr/include/X11/Xlib.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
typedef struct WINDOW_STRUCT{
    const char* title;
    int xp, yp, width, height;
    uint32_t* pixels;
    Display* display;
    Window window;
    Window root;
    XImage *content;
} window;

window* Window_init(const char* title, int width, int height, int xp, int yp, uint32_t* pixels);

void Window_update(Window* window);

#endif 
