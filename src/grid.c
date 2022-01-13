#include <stdio.h>
#include <stdlib.h>

#include "tools.h"
#include "grid.h"



//constructeur - destructeur
grid* grid_create(int w, int h)
{
	grid* tab = tools_malloc(sizeof(grid));
	
	tab->w = w;
	tab->h = h;	
	
	//create tab
	tab->data = tools_malloc(sizeof(int*) * h);
	for(int i = 0;i < h; i++)
		tab->data[i] = tools_malloc(sizeof(int) * w);
	
	//init value
	for(int i = 0; i < h; i++)
	{
		for(int j = 0; j < w; j++)
			tab->data[i][j] = 0;
	}

	//create check_array2D
	tab->check_data = tools_malloc(sizeof(int*) * h);
	for(int i = 0; i < h; i++)
		tab->check_data[i] = tools_malloc(sizeof(int) * w);	
	
	return tab;
	
}

void grid_destroy(grid* tab)
{
	//memory liberation for array2D
	for(int i = 0; i < tab->h; i++)
		tools_free(tab->data[i], sizeof(int) * tab->w);
	tools_free(tab->data, sizeof(int*) * tab->h);

	//memory liberation for check_array2D
	for(int i = 0; i < tab->h; i++)
		tools_free(tab->check_data[i], sizeof(int) * tab->w);
	tools_free(tab->check_data, sizeof(int*) * tab->h);

	//memory libertion for the struct 
	tools_free(tab, sizeof(grid));
}


//Tools
void grid_debug(grid* tab)
{
	for(int i = 0; i < tab->h; i ++)
	{
		for(int j = 0; j < tab->w; j++)
			fprintf(stderr, "%d", tab->data[i][j]);
		
		fprintf(stderr, "\n");	
	}

}

void grid_set(grid* tab, int w, int h, int value)
{
	//error management 
	if((w >= tab->w) || (w < 0) || (h >= tab->h) || (h < 0) )
	{
		fprintf(stderr, "ERROR <grid_set> : Impossible d'ajouter une valeur dans l'index w=%d h=%d\n(max -> w=%d / h=%d)\n\n",w, h, tab->w  - 1, tab->h - 1);
		return; 
	}
	if((value < 0) || (value > 1))
	{
		fprintf(stderr, "ERROR <grid_set> : Valeur incorecte : value = %d\n(valide 1 ou 0)\n\n", value);
		return;
	}


	//set value
	tab->data[h][w] = value; 
}

void grid_init(grid* tab, int value)
{
	for(int i = 0; i < tab->h; i++)
	{
		for(int j = 0; j < tab->w; j++)
			tab->check_data[i][j] = value;
	}	
}

// GAME LIFE

void grid_check(grid* tab)
{
	int i, j;

	grid_init(tab, 0);
	
	//check neighbour cell	
	for(i = 0; i < tab->h; i++)
	{
		for(j = 0; j < tab->w; j++)
		{	
       			check_horizontal(tab, j, i);
		}

		check_vertical(tab, j, i);	
	}
	
	printf("cell : %d\n", tab->check_data[4][3]);
	//set live cell 
	for(i = 0; i < tab->h; i++)
	{
		for(j = 0; j < tab->w; j++)
		{	
			if(tab->check_data[i][j] < 2)
				tab->data[i][j] = 0;
			else if(tab->check_data[i][j] > 3)
				tab->data[i][j] = 0;
			else
				tab->data[i][j] = 1;	
		}
	}

}

void check_horizontal(grid* tab, int w, int h)
{
	//check x - 1
	if(tab->data[h][w - 1] == 1)
		tab->check_data[h][w] ++;
	//check x + 1
	if(tab->data[h][w + 1] == 1)
		tab->check_data[h][w] ++;
}

void check_vertical(grid* tab, int w, int h)
{
	//check y - 1
	if(h > 0)
	{
		if(tab->data[h - 1][w] == 1)
		{
			tab->check_data[h][w] ++;
			printf("sa marche\n");
		}
	}
	//check y + 1
	if(h < tab->h - 1)
	{
		if(tab->data[h + 1][w] == 1)
			tab->check_data[h][w] ++;
	}
}

