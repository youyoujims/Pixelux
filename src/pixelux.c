#include "headers/pixelux.h"
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

static void pixelux_fill_pixel(uint32_t *pixels, size_t width, size_t height, int xp, int yp, int color){
    uint32_t col = (((color>>24) &0xff) < 255) ? pixelux_mix_colors(pixels[xp + yp * width], color) : (uint32_t) color;
    pixels[xp + yp * width] = col;
}

void pixelux_fill_rect(uint32_t *pixels, size_t width, size_t height, int xp, int yp, int w, int h, int color){
    for(int y = 0; y < h; y++){
        int ya = y + yp;
        for(int x = 0; x < w; x++){
            int xa = x + xp;
            if(xa < 0 || xa >= width || ya < 0 || ya >= height) continue;
            pixelux_fill_pixel(pixels, width, height, xa, ya, color);
        }
    }
}

void pixelux_draw_rect(uint32_t *pixels, size_t width, size_t height, int xp, int yp, int w, int h, int thickness,  int color){
    for(int x = xp; x < xp + w; x++){
        if(x < 0 && x > width) continue;
        pixelux_fill_pixel(pixels, width, height, x, yp, color);
        for(int i = 0; i < thickness; i++){
            if ((yp + h - i) >= 0 && (yp + h - i) < height) {
                pixelux_fill_pixel(pixels, width, height, x, yp-i, color);
                pixelux_fill_pixel(pixels, width, height, x, (yp + h)-i, color);
            }
        }
    }
    for(int y = yp; y <= yp + h; y++){
         if(y < 0 && y > width) continue;
         pixelux_fill_pixel(pixels, width, height, xp, y, color);
         for(int i = 0; i < thickness; i++){
             if((xp + w - i) >= 0 && (xp + w - i) < width){
                pixelux_fill_pixel(pixels, width, height, xp + i, y, color);
                pixelux_fill_pixel(pixels, width, height, ((xp + w)-i-1), y, color);
             }
         }
    }
} 

void pixelux_fill_circle(uint32_t *pixels, size_t width, size_t height, int xp, int yp, int r, int color){
   int x1 = xp - r;
   int y1 = yp - r;
   int x2 = xp + r;
   int y2 = yp + r;
   for(int y = y1; y < y2; y++){
       for(int x = x1; x < x2; x++){
            if(x >= 0 && x < width && y >= 0 && y < height){
                int dx = x - xp;
                int dy = y - yp;

                if(dx*dx + dy*dy <= r*r){
                    pixelux_fill_pixel(pixels, width, height, x, y, color);
                }
            }
       }
   }
}

void pixelux_gradient_rect(uint32_t *pixels, size_t width, size_t height, int xp, int yp, int w, int h, int color1, int color2){
    pixelux_fill_rect(pixels, width, height, xp, yp, w, h, color1);
    for(int y = 0; y < h; y++){
        for(int x = 0; x < w; x++){
            double value = (double) (((double)x / (double)w)*1);
            uint8_t r = color2&0xff;
            uint8_t g = (color2>>8)&0xff;
            uint8_t b = (color2>>16)&0xff;
            uint8_t a = (uint8_t) (255 * value);
             
            pixelux_fill_pixel(pixels, width, height, x, y,((a << 24) | (b << 16) | (g << 8) | r));   
        }
    }
}

uint32_t pixelux_mix_colors(uint32_t color1, uint32_t color2){
    uint8_t r1 = color1&0xff;
    uint8_t g1 = (color1>>8)&0xff;
    uint8_t b1 = (color1>>16)&0xff;
    uint8_t alpha1 = (color1>>24)&0xff;
    
    uint8_t r2 = color2&0xff;
    uint8_t g2 = (color2>>8)&0xff;
    uint8_t b2 = (color2>>16)&0xff;
    uint8_t alpha2 = (color2>>24)&0xff;
    
    float a2 = alpha2 / 255.0f;
    
    uint8_t r = (uint8_t) (r1 * (1 - a2) + r2 * a2);
    uint8_t g = (uint8_t) (g1 * (1 - a2) + g2 * a2);
    uint8_t b = (uint8_t) (b1 * (1 - a2) + b2 * a2);
    uint8_t a = alpha1;

    return (a << 24) | (b << 16) | (g << 8) | r;   
}

uint32_t pixelux_rgba_to_hex(uint32_t r, uint32_t g, uint32_t b, uint32_t a){
    return (a << 24) | (b << 16) | (g << 8) | r;
}

int pixelux_make_file(uint32_t *pixels, size_t width, size_t height, const char* fileName){
    int result = 0;
    FILE* file = fopen(fileName, "wb");
    if(!file){
        printf("Couldn't create the file.\n");
        result = 1;
        goto exit;
    }
    fprintf(file, "P6\n%zu %zu 255\n", width, height);
    for(int i = 0; i < width*height;i++){
        uint32_t pixel = pixels[i];
        uint8_t bytes[3] = {
            pixel&0xff,
            (pixel>>(8))&0xff,
            (pixel>>(16))&0xff
        };
        fwrite(bytes,sizeof(bytes), 1, file);
        if(ferror(file)){
            printf("Couldn't put the data of the image inside of the file\n");
            result = 1;
            goto exit;
        }
    }
    
exit:
    if(file) fclose(file);
    return result;
} 
