#include <SDL2/SDL.h>

#include "SL_GameEngine.h"
#include "SL_TextureManager.h"

class MyGameEngine : public SL_GameEngine
{

private:
	SDL_Texture *_shipTexture;
	SDL_Rect _sourceRect;
	SDL_Rect _destinationRect;
	int _xSpeed;
	int _ySpeed;

public:
	void createShipTexture()
	{
		_shipTexture = SL_TextureManager::loadTexture("assets/playerShip2_red.png", getRenderer());
		if (_shipTexture != NULL)
		{
			_sourceRect.x = _sourceRect.y = 0;
			_sourceRect.w = 112;
			_sourceRect.h = 75;

			_destinationRect.w = 112;
			_destinationRect.h = 75;
			_destinationRect.x = round((getWidth() / 2.0) - (_destinationRect.w / 2.0));
			_destinationRect.y = round((getHeight() / 2.0) - (_destinationRect.h / 2.0));

			_xSpeed = 0;
			_ySpeed = 0;
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
				if(_ySpeed > -10){
					_ySpeed--;
				}
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_DOWN)
			{
				if(_ySpeed < 10){
					_ySpeed++;
				}
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_LEFT)
			{
				if(_xSpeed > -10)
				{
					_xSpeed--;
				}
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT)
			{
				if(_xSpeed < 10)
				{
					_xSpeed++;
				}
			}
			break;
		}
	}

	void update()
	{
		_destinationRect.x += round(_xSpeed * getMillisecondsSinceLastLoop() / 40.0);
		_destinationRect.y += round(_ySpeed * getMillisecondsSinceLastLoop() / 40.0);
		if((_destinationRect.x < 0) || ((_destinationRect.x + _destinationRect.w) > getWidth()))
		{
			_xSpeed *= -1;
		}
		if((_destinationRect.y < 0) || ((_destinationRect.y + _destinationRect.h) > getHeight()))
		{
			_ySpeed *= -1;
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

	if (engine->setup("My Example Game", 1024, 768, false, 25) == 0)
	{
		engine->setBackground(32, 32, 32);
		engine->createShipTexture();

		engine->run();

		engine->cleanupShipTexture();
		engine->teardown();
	}

	delete engine;

	return 0;
}