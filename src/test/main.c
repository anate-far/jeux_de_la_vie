#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>

#include "tools.h"
#include "grid.h"

int main(void)
{
	tools_memory_init();

	
	grid* tab = grid_create(100, 100);
	grid_set(tab, 3, 3, 1);
	grid_set(tab, 3, 4, 1);
	grid_set(tab, 3, 5, 1);
	grid_set(tab, 3, 6, 1);
	
	grid_set(tab, 4 , 4, 1);
	grid_set(tab, 5, 4, 1);
	grid_set(tab, 6, 4, 1);

	grid_debug(tab, tab->data);
	printf("\n");

	for(int i = 0; i < 3; i++)
	{
		grid_check(tab);
		grid_debug(tab, tab->data);
		printf("\n");
	}


	grid_destroy(tab);


	return EXIT_SUCCESS;
}
