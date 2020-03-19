#include <SDL2/SDL.h>

#include "SL_GameEngine.h"
#include "SL_TextureManager.h"

class MyGameEngine : public SL_GameEngine
{

private:
	SDL_Texture *_shipTexture;
	SDL_Rect _sourceRect;
	SDL_Rect _destinationRect;

public:
	void createShipTexture()
	{
		_shipTexture = SL_TextureManager::loadTexture("assets/playerShip2_red.png", getRenderer());
		if (_shipTexture != NULL)
		{
			_sourceRect.x = _sourceRect.y = 0;
			_sourceRect.w = 112;
			_sourceRect.h = 75;

			_destinationRect.x = 200;
			_destinationRect.y = 150;
			_destinationRect.w = 112;
			_destinationRect.h = 75;
		}
	}

	void cleanupShipTexture()
	{
		if (_shipTexture != NULL)
		{
			SL_TextureManager::destroyTexture(_shipTexture);
		}
	}

	void handleEvent(SDL_Event event)
	{
		switch (event.type)
		{
		case SDL_KEYDOWN:
			if (event.key.keysym.scancode == SDL_SCANCODE_UP)
			{
				_destinationRect.y -= 5;
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_DOWN)
			{
				_destinationRect.y += 5;
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_LEFT)
			{
				_destinationRect.x -= 5;
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT)
			{
				_destinationRect.x += 5;
			}
			break;
		}
	}

	void render()
	{
		SDL_RenderCopy(getRenderer(), _shipTexture, &_sourceRect, &_destinationRect);
	}
};

int main()
{
	MyGameEngine *engine = new MyGameEngine();

	if (engine->setup("My Example Game", 800, 640, false, 25) == 0)
	{
		engine->setBackground(127, 127, 127);
		engine->createShipTexture();

		engine->run();

		engine->cleanupShipTexture();
		engine->teardown();
	}

	delete engine;

	return 0;
}