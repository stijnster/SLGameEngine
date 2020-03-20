#ifndef SL_TEXTUREMANAGER_H
#define SL_TEXTUREMANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

struct SL_TextureWidthAndHeight {
	SDL_Texture *texture;
	int w;
	int h;
};

class SL_TextureManager
{
public:
	static SDL_Texture *loadTexture(const char *filename, SDL_Renderer *renderer);
	static SL_TextureWidthAndHeight loadTextureWithAndHeight(const char *filename, SDL_Renderer *renderer);
	static void destroyTexture(SDL_Texture *texture);
};

#endif
