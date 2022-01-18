#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>

#include "tools.h"
#include "grid.h"
#include "ui.h"

#define NB_CELL 80
#define SIZE_WINDOW_W 800
#define SIZE_WINDOW_H 900
#define SIZE_BUTTON_W 200
#define SIZE_BUTTON_H 100
#define POS_BUTTON_X 600
#define POS_BUTTON_Y 800
#define SIZE_RULES_W 600
#define SIZE_RULES_H 100
#define POS_RULES_X 0
#define POS_RULES_Y 800
#define DELAY 100 // milliseconde

int main(void)
{
	tools_memory_init();

	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_bool window_is_open = SDL_TRUE;
	SDL_Surface* icon = IMG_Load("../img/coeur.ico");


	grid* tab = grid_create(NB_CELL, NB_CELL);

	//génération aléatoire des cellue
	srand(time(NULL));
	generate_cell(tab, NB_CELL);
	
	//grid_set(tab, 4, 3, 1);
	//grid_set(tab, 5, 3, 1);

	SDL_Init(SDL_INIT_VIDEO);

	if(SDL_CreateWindowAndRenderer(SIZE_WINDOW_W, SIZE_WINDOW_H,0, &window, &renderer) != 0)
		fprintf(stderr, "Impossible de creer la fenetre et le rendu\n");


	//mise en place de l'icone
	SDL_SetWindowIcon(window, icon);
	

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

				case SDL_MOUSEBUTTONDOWN:	
					if((event.button.x <= 800) && (event.button.x >= 600))
					{
						if((event.button.y <= 900) && (event.button.y >= 800))
						{
							grid_init(tab, tab->data, 0);
							SDL_RenderClear(renderer);
							generate_cell(tab, NB_CELL);
						}
					}
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
		display_button(renderer, POS_BUTTON_X, POS_BUTTON_Y, SIZE_BUTTON_W, SIZE_BUTTON_H, "../src/img/button.jpeg");	
		display_button(renderer, POS_RULES_X, POS_RULES_Y, SIZE_RULES_W, SIZE_RULES_H, "../src/img/rules.jpg");

		SDL_RenderPresent(renderer);
	}

	grid_destroy(tab);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	tools_check_at_end_of_app();

	return EXIT_SUCCESS;
}
