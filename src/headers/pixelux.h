#ifndef PIXEL_LUX_HEADER
#define PIXEL_LUX_HEADER
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
void pixelux_fill_rect(uint32_t *pixels, size_t width, size_t height, int xp, int yp, int w, int h, int color);

void pixelux_draw_rect(uint32_t *pixels, size_t width, size_t height, int xp, int yp, int w, int h, int thickness, int color);

void pixelux_fill_circle(uint32_t *pixels, size_t width, size_t height, int xp, int yp, int r, int color);

/* -The colors must have a alpha value. If your color is 0xff00ff(pink) then it must be 0xffff00ff (the first two ff define the opacity*/
void pixelux_gradient_rect(uint32_t *pixels, size_t width, size_t height, int xp, int yp, int w, int h, int color1, int color2);

uint32_t pixelux_mix_colors(uint32_t color1, uint32_t color2);

uint32_t pixelux_rgba_to_hex(uint32_t r, uint32_t g, uint32_t b, uint32_t a);

int pixelux_make_file(uint32_t *pixels, size_t width, size_t height, const char* fileName);

#endif
