#include "SL_TextureManager.h"

SDL_Texture *SL_TextureManager::loadTexture(const char *filename, SDL_Renderer *renderer)
{
	SL_TextureWidthAndHeight textureWidthAndHeight;

	textureWidthAndHeight = loadTextureWithAndHeight(filename, renderer);

	return textureWidthAndHeight.texture;
}

SL_TextureWidthAndHeight SL_TextureManager::loadTextureWithAndHeight(const char *filename, SDL_Renderer *renderer)
{
	SL_TextureWidthAndHeight textureWidthAndHeight;

	SDL_Surface *surface = IMG_Load(filename);

	textureWidthAndHeight.texture = SDL_CreateTextureFromSurface(renderer, surface);
	textureWidthAndHeight.w = surface->w;
	textureWidthAndHeight.h = surface->h;

	SDL_FreeSurface(surface);

	return textureWidthAndHeight;
}

void SL_TextureManager::destroyTexture(SDL_Texture *texture)
{
	SDL_DestroyTexture(texture);
}