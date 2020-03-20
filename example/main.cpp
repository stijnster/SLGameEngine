#include <SDL2/SDL.h>

#include "SL_GameEngine.h"
#include "SL_TextureManager.h"
#include "SL_GameObject.h"

class MyGameEngine : public SL_GameEngine
{

private:
	SL_GameObject *_ship;
	int _xSpeed;
	int _ySpeed;

public:
	void createShip()
	{
		_xSpeed = 0;
		_ySpeed = 0;

		_ship = new SL_GameObject("assets/playerShip2_red.png", getRenderer(), 0, 0, 112, 75);
		_ship->setXY((getWidth() / 2.0), (getHeight() / 2.0));
	}

	void cleanupShip()
	{
		delete _ship;
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
		if(_ship != NULL)
		{
			_ship->setXY(_ship->getX() + (_xSpeed * getMillisecondsSinceLastLoop() / 40.0), _ship->getY() + (_ySpeed * getMillisecondsSinceLastLoop() / 40.0));
			if((_ship->getX() < 0) || (_ship->getX() > getWidth()))
			{
				_xSpeed *= -1;
			}
			if((_ship->getY() < 0) || (_ship->getY() > getHeight()))
			{
				_ySpeed *= -1;
			}

			_ship->update();
		}
	}

	void render()
	{
		if(_ship != NULL)
		{
			_ship->render();
		}
	}
};

int main()
{
	MyGameEngine *engine = new MyGameEngine();

	if (engine->setup("My Example Game", 640, 480, false, 30) == 0)
	{
		engine->setBackground(32, 32, 32);
		engine->createShip();

		engine->run();

		engine->cleanupShip();
		engine->teardown();
	}

	delete engine;

	return 0;
}