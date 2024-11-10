#ifndef WINDOW_HEADER
#define WINDOW_HEADER
#include </usr/include/X11/Xlib.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
typedef struct WINDOW_STRUCT{
	Display* display;
	Window root;
	Window win;
}window;

window* init_window(const char* title, int x, int y, int width, int height, uint32_t flags);
void show(window* window);
#endif
