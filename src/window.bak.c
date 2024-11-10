#include "headers/window.h"

window* init_window(const char* title, int x, int y, int width, int height, uint32_t flags){
	window* window = calloc(1, sizeof(struct WINDOW_STRUCT));
	if(!window){
		printf("Error: Couldn't open X window\n");
		exit(1);
	}
	window->display = XOpenDisplay(0);
	window->root = XDefaultRootWindow(window->display);
	window->win = XCreateSimpleWindow(window->display, window->root, x, y, width, height, 0, 0, 0);
	if(!window->win){
		printf("Couldn't make the window\n");
		exit(1);
	}
	XStoreName(window->display, window->win, title);
	XFlush(window->display);
	return window;
}

void show(window* window){
	XMapWindow(window->display, window->win);
	XFlush(window->display);
	XEvent event;
	Atom wmDeleteMessage = XInternAtom(window->display, "WM_DELETE_WINDOW", False);
	while(1){
		XNextEvent(window->display, &event);
		if (event.type == ClientMessage && (Atom)event.xclient.data.l[0] == wmDeleteMessage) {
            break;
        }
	}
	XCloseDisplay(window->display);
}

