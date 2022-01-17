#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>


#include "tools.h"
#include "ui.h"
#include "grid.h"


void display_cell(SDL_Renderer* renderer, grid* tab, int delay)
{
	SDL_Texture* cell_live_texture = create_texture(renderer, "img/life_cell.png");
	SDL_Texture* cell_death_texture = create_texture(renderer, "img/death_cell.png");
	SDL_Rect position = {0, 0, SIZE_CELL_W, SIZE_CELL_H};

	int x = 0, y = 0;

	//initialisation du rendu
	SDL_QueryTexture(cell_live_texture, NULL, NULL, &position.w, &position.h);
	SDL_QueryTexture(cell_death_texture, NULL, NULL, &position.w, &position.h);

	//affichage
	for(int i = 0; i < tab->size_tab_1D; i++)
	{
		if(x == tab->w)
		{
			x = 0;
			y++;
		}
		position.y = y * SIZE_CELL_H;
		position.x = x * SIZE_CELL_W;

		if(tab->data[i] == 1)
			SDL_RenderCopy(renderer, cell_live_texture, NULL, &position);
		else
			SDL_RenderCopy(renderer, cell_death_texture,NULL, &position);

		x ++;
	}
	

	SDL_Delay(delay);
}

SDL_Texture* create_texture(SDL_Renderer* renderer, char* name_img)
{
	SDL_Surface* img = IMG_Load(name_img);
	if(name_img == NULL)
		fprintf(stderr,"ERROR <set_texture> : Impossible de charger l image %s\n", name_img);

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, img);
	if(texture == NULL)
		fprintf(stderr,"Error <set_texture> : Impossible de charger la texture de l'image %s\n", name_img);

	SDL_FreeSurface(img);
	

	return texture;
}
