#ifndef GRID_H
#define GRID_H

#define DEATH 0
#define LIVE 1

typedef struct{
	int* data;
	int* check_data; 
	int w;
	int h;
	int size_tab_1D;
}grid;

//constructeur - destructeur
grid* grid_create(int w, int h);
void grid_destroy(grid* tab);

//Tools
void grid_debug(grid* tab, int* data);
void grid_set(grid* tab, int x, int y, int value);
int get_index_1D(grid* tab, int x, int y);
void grid_init(grid* tab,int* data, int value);

// GAME LIFE
void grid_check(grid* tab);
void check_horizontal(grid* tab);
void check_vertical(grid* tab);
void check_diagonal(grid* tab);


#endif
