#include <stdio.h>
#include <stdlib.h>

#include "tools.h"
#include "grid.h"



//constructeur - destructeur
grid* grid_create(int w, int h)
{
 	grid* tab = tools_malloc(sizeof(grid));

	//init value
	tab->w = w;
	tab->h = h;
	tab->size_tab_1D = w * h;

	//init array 2D
	tab->data = tools_malloc(sizeof(int) * tab->size_tab_1D);
	tab->check_data = tools_malloc(sizeof(int) * tab->size_tab_1D);

	//set start value in array 2D (0)
	grid_init(tab, tab->data, 0);
	grid_init(tab, tab->check_data, 0);

	return tab;
}

void grid_destroy(grid* tab)
{
	//liberation memory from array 2D
	tools_free(tab->data, sizeof(int) * tab->size_tab_1D);
	tools_free(tab->check_data, sizeof(int) * tab->size_tab_1D);

	//liberation memory struct
	tools_free(tab, sizeof(grid));
}


//Tools
void grid_debug(grid* tab, int* data)
{
	int size_x = 0;
	for(int i = 0; i < tab->size_tab_1D; i++)
	{
		if(size_x == tab->w)
		{
			printf("\n");
			size_x = 0;
		}
		size_x ++;

		printf("%d",data[i]);
	}
	printf("\n");


}

void grid_set(grid* tab, int x, int y, int value)
{
	int index = get_index_1D(tab, x, y);
       	tab->data[index] = value;	
}

int get_index_1D(grid* tab, int x, int y)
{
	int index = y * tab->w  + x; 
	return index;	
}

void grid_init(grid* tab,int* data, int value)
{
	for(int i = 0; i < tab->size_tab_1D; i++)
		data[i] = value;
}

// GAME LIFE
void grid_check(grid* tab)
{
	grid_init(tab, tab->check_data, 0);
	int i = 0;

	check_vertical(tab);
	check_horizontal(tab);
	check_diagonal(tab);
	printf("tab : %d\n", tab->check_data[21]);
	

	for(i = 0; i < tab->size_tab_1D; i++)
	{
		if((tab->check_data[i] == 2) && (tab->data[i] == 1))
			tab->data[i] = 1;
		else if(tab->check_data[i] == 3)
			tab->data[i] = 1;
		else
			tab->data[i] = 0;
	}

}
void check_horizontal(grid* tab)
{
	for(int i = 0; i < tab->size_tab_1D; i++)
	{
		if(tab->data[i - 1] == 1)
		       tab->check_data[i] ++;	
		if(tab->data[i + 1] == 1)
		       tab->check_data[i] ++;	
	}

}
void check_vertical(grid* tab)
{
	for(int i = 0; i < tab->size_tab_1D; i++)
	{
		if(tab->data[i - tab->w] == 1)
		       tab->check_data[i] ++;	
		if(tab->data[i + tab->w] == 1)
		       tab->check_data[i] ++;	
	}

}

void check_diagonal(grid* tab)
{
	for(int i = 0; i < tab->size_tab_1D; i++)
	{
		if(tab->data[i - (tab->w - 1)] == 1)
		       tab->check_data[i] ++;
		if(tab->data[i - (tab->w  + 1)] == 1)
		       tab->check_data[i] ++;	
		if(tab->data[i + (tab->w - 1)] == 1)
		       tab->check_data[i] ++;	
		if(tab->data[i + (tab->w  + 1)] == 1)
		       tab->check_data[i] ++;
	}

}

