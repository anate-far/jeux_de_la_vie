#ifndef UI_H
#define UI_H

#include "grid.h"

#define SIZE_CELL_W 10
#define SIZE_CELL_H 10

void display_cell(SDL_Renderer* renderer, grid* tab, int delay);
SDL_Texture* create_texture(SDL_Renderer* renderer, char* name_img);

#endif
