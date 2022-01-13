#ifndef GRID_H
#define GRID_H

#define DEATH 0
#define LIVE 1

typedef struct{
	int** data;
	int** check_data; 
	int w;
	int h;	
}grid;

//constructeur - destructeur
grid* grid_create(int w, int h);
void grid_destroy(grid* tab);

//Tools
void grid_debug(grid* tab);
void grid_set(grid* tab, int w, int h, int value);
void grid_init(grid* tab, int value);

// GAME LIFE
void grid_check(grid* tab);
void check_horizontal(grid* tab, int w, int h);
void check_vertical(grid* tab, int w, int h);

#endif
