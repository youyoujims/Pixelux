#include <stdio.h>
#include <stdlib.h>
#include "headers/pixelux.h"
#include <string.h>
#define WIDTH 800
#define HEIGHT 600
static uint32_t pixels[WIDTH*HEIGHT];

int string_ends_with(const char * str, const char * suffix)
{
  int str_len = strlen(str);
  int suffix_len = strlen(suffix);

  return 
    (str_len >= suffix_len) &&
    (0 == strcmp(str + (str_len-suffix_len), suffix));
}

int main(int argc, char** argv){
    if(argc != 2){
        printf("\033[0;31m\e[1mError\e[1m: You must add the name of the file.\n\033[0m");
        return 1;
    }
    if(string_ends_with(argv[1], ".ppm") == 0){
        printf("\033[0;31m\e[1mError\e[1m: The name of the file must ends with .ppm \n\033[0m");
        return 1;
    }
    pixelux_gradient(pixels, WIDTH, HEIGHT, 0, 0, WIDTH, HEIGHT, 0xffff00ff, 0xffff0000);
    pixelux_make_file(pixels, WIDTH, HEIGHT, argv[1]);
    return EXIT_SUCCESS;
}
