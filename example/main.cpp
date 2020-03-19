#include <SDL2/SDL.h>

#include "SL_GameEngine.h"
#include "SL_GameController.h"
#include "SL_TextureManager.h"

class MyGameController : public SL_GameController
{
private:
	SDL_Texture *_shipTexture;
	SDL_Rect _sourceRect;
	SDL_Rect _destinationRect;

public:
	void beforeRun()
	{
		_shipTexture = SL_TextureManager::loadTexture("assets/playerShip2_red.png", _gameEngine->getRenderer());
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

	void afterRun()
	{
		if (_shipTexture != NULL)
		{
			SL_TextureManager::destroyTexture(_shipTexture);
		}
	}

	void startRender()
	{
		SDL_RenderCopy(_gameEngine->getRenderer(), _shipTexture, &_sourceRect, &_destinationRect);
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
};

int main()
{
	SL_GameEngine *engine = new SL_GameEngine();

	if (engine->setup("My Example Game", 800, 640, false, 25) == 0)
	{
		MyGameController *controller = new MyGameController();

		controller->beforeUpdate();

		engine->setGameController(controller);
		engine->setBackground(127, 127, 127);

		engine->run();
		engine->teardown();

		delete controller;
	}

	delete engine;

	return 0;
}