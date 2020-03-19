#ifndef SL_TEXTUREMANAGER_H
#define SL_TEXTUREMANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class SL_TextureManager
{

public:
	static SDL_Texture *loadTexture(const char *filename, SDL_Renderer *renderer);
	static void destroyTexture(SDL_Texture *texture);
};

#endif
