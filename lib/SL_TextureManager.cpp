#include "SL_TextureManager.h"

SDL_Texture *SL_TextureManager::loadTexture(const char *filename, SDL_Renderer *renderer)
{
	SDL_Texture *texture;

	SDL_Surface *surface = IMG_Load(filename);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	return texture;
}