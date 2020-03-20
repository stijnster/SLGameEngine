#include <SDL2/SDL.h>

#include "SL_GameEngine.h"
#include "SL_TextureManager.h"
#include "SL_GameObject.h"

class Player : public SL_GameObject
{
public:
	void handleEvent(SDL_Event event)
	{
		switch (event.type)
		{
		case SDL_KEYDOWN:
			if (event.key.keysym.scancode == SDL_SCANCODE_UP)
			{
				if (getVelocityY() > -100.0)
				{
					setVelocityY(getVelocityY() - 50.0);
				}
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_DOWN)
			{
				if (getVelocityY() < 100.0)
				{
					setVelocityY(getVelocityY() + 50.0);
				}
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_LEFT)
			{
				if (getVelocityX() > -100.0)
				{
					setVelocityX(getVelocityX() - 50.0);
				}
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT)
			{
				if (getVelocityX() < 100.0)
				{
					setVelocityX(getVelocityX() + 50.0);
				}
			}
			break;
		}
	}
};
class MyGameEngine : public SL_GameEngine
{

private:
	Player *_ship;

	SL_GameObject *_enemy;
	SL_GameObject *_enemy2;

	int _xSpeed;
	int _ySpeed;

public:
	void createShip()
	{
		_xSpeed = 0;
		_ySpeed = 0;

		_ship = new Player();
		_ship->setup("assets/playerShip2_red.png", getRenderer(), 0, 0, 56, 36);
		_ship->setXY((getWidth() / 2.0), (getHeight() / 2.0));

		_enemy = new SL_GameObject();
		_enemy->setup("assets/enemyBlue3.png", getRenderer(), 0, 0, 51, 41);
		_enemy->setXY(100, 200);
		_enemy->setVelocityX(220.0);
		_enemy->setVelocityY(80.0);

		_enemy2 = new SL_GameObject();
		_enemy2->setup("assets/enemyBlue4.png", getRenderer(), 0, 0, 41, 42);
		_enemy2->setXY(100, 200);
		_enemy2->setVelocityX(-60.0);
		_enemy2->setVelocityY(90.0);
	}

	void cleanupShip()
	{
		_enemy2->teardown();
		delete _enemy2;
		_enemy->teardown();
		delete _enemy;
		_ship->teardown();
		delete _ship;
	}

	void handleEvent(SDL_Event event)
	{
		_ship->handleEvent(event);
	}

	void boundsBounce(SL_GameObject *object)
	{
		if (object->getX() - (object->getWidth() / 2.0) < 0)
		{
			object->setVelocityX(object->getVelocityX() * -1);
			object->setX(object->getWidth() / 2.0);
		}
		if (object->getX() + (object->getWidth() / 2.0) > getWidth())
		{
			object->setVelocityX(object->getVelocityX() * -1);
			object->setX(getWidth() - (object->getWidth() / 2.0));
		}
		if (object->getY() - (object->getHeight() / 2.0) < 0)
		{
			object->setVelocityY(object->getVelocityY() * -1);
			object->setY(object->getHeight() / 2.0);
		}
		if (object->getY() + (object->getHeight() / 2.0) > getHeight())
		{
			object->setVelocityY(object->getVelocityY() * -1);
			object->setY(getHeight() - (object->getHeight() / 2.0));
		}
	}

	void update()
	{
		_ship->update();
		boundsBounce(_ship);

		_enemy->update();
		boundsBounce(_enemy);

		_enemy2->update();
		boundsBounce(_enemy2);
	}

	void render()
	{
		_enemy->render();
		_enemy2->render();
		_ship->render();
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