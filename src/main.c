#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>

#include "tools.h"
#include "grid.h"
#include "ui.h"

#define NB_CELL 100
#define SIZE_WINDOW 1000
#define DELAY 100 // milliseconde

int main(void)
{
	tools_memory_init();

	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_bool window_is_open = SDL_TRUE;

	
	grid* tab = grid_create(NB_CELL, NB_CELL);

	//génération aléatoire des cellue
	srand(time(NULL));
	int nb_create_cell = rand()%NB_CELL * NB_CELL;
	int x_rendom, y_rendom;
	for(int i = 0; i <= nb_create_cell; i++)
	{
		x_rendom = rand()%NB_CELL;
		y_rendom = rand() % NB_CELL;	
		grid_set(tab, x_rendom, y_rendom, 1);
	}
	
	//grid_set(tab, 4, 3, 1);
	//grid_set(tab, 5, 3, 1);

	SDL_Init(SDL_INIT_VIDEO);

	if(SDL_CreateWindowAndRenderer(SIZE_WINDOW, SIZE_WINDOW,0, &window, &renderer) != 0)
		fprintf(stderr, "Impossible de creer la fenetre et le rendu\n");
	

	while(window_is_open)
	{
		SDL_Event event;
		while((SDL_PollEvent(&event)))
		{
			switch(event.type)
			{
				case SDL_QUIT:
					window_is_open = SDL_FALSE;
					break;
				
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym)
					{
						case SDLK_ESCAPE:
							window_is_open = SDL_FALSE;
							break;
						
						default:
							continue;
					}

					break;

				default:
					break;
			}
		}


		SDL_RenderClear(renderer);
		
		grid_check(tab);

		display_cell(renderer, tab, DELAY);	

		SDL_RenderPresent(renderer);
	}

	grid_destroy(tab);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	tools_check_at_end_of_app();

	return EXIT_SUCCESS;
}
