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
	SL_GameObject *_laser;

public:
	void createShip()
	{
		_ship = new Player();
		_ship->setup("assets/playerShip2_red.png", getRenderer(), (getWidth() / 2.0), (getHeight() / 2.0), 56, 36);
		_ship->hitpoints = 20;

		_enemy = new SL_GameObject();
		_enemy->setup("assets/enemyBlue3.png", getRenderer(), 100, 50, 51, 41);
		_enemy->setVelocityX(220.0);
		_enemy->setVelocityY(80.0);
		_enemy->hitpoints = 35;

		_enemy2 = new SL_GameObject();
		_enemy2->setup("assets/enemyBlue4.png", getRenderer(), getWidth() - 100, 80, 41, 42);
		_enemy2->setVelocityX(-60.0);
		_enemy2->setVelocityY(90.0);
		_enemy2->hitpoints = 45;

		_laser = new SL_GameObject();
		_laser->setup("assets/laserRed03.png", getRenderer(), -100, -100, 4, 18);
		_laser->setVelocityY(-300.0);
	}

	void cleanupShip()
	{
		_laser->teardown();
		delete _laser;
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

		switch (event.type)
		{
		case SDL_KEYDOWN:
			if (event.key.keysym.scancode == SDL_SCANCODE_SPACE)
			{
				printf("space pressed\n");
				if (!(_laser->isActive()))
				{
					printf("activating laser\n");
					_laser->setXY(_ship->getX(), _ship->getY());
					_laser->setActive(true);
				}
			}
			break;
		}
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

		_laser->update();
		if ((_laser->getY() < -50) || (_laser->getY() > getHeight() + 50))
		{
			_laser->setActive(false);
		}

		if (_laser->isActive())
		{
			if (_enemy->isActive())
			{
				if (_laser->collidesWith(_enemy))
				{
					_enemy->hitpoints -= 10;
					_laser->setActive(false);
				}
			}

			if (_enemy2->isActive())
			{
				if (_laser->collidesWith(_enemy2))
				{
					_enemy2->hitpoints -= 10;

					_laser->setActive(false);
				}
			}
		}

		if (_enemy->isActive())
		{
			if (_ship->collidesWith(_enemy))
			{
				_ship->hitpoints -= 2;
				_enemy->hitpoints -= 2;
				if (_ship->getX() < _enemy->getX())
				{
					_ship->setVelocityX(abs(_ship->getVelocityX()) * -1);
					_enemy->setVelocityX(abs(_enemy->getVelocityX()));
				}
				else
				{
					_ship->setVelocityX(abs(_ship->getVelocityX()));
					_enemy->setVelocityX(abs(_enemy->getVelocityX()) * -1);
				}
				if (_ship->getY() < _enemy->getY())
				{
					_ship->setVelocityY(abs(_ship->getVelocityY()) * -1);
					_enemy->setVelocityY(abs(_enemy->getVelocityY()));
				}
				else
				{
					_ship->setVelocityY(abs(_ship->getVelocityY()));
					_enemy->setVelocityY(abs(_enemy->getVelocityY()) * -1);
				}
			}
		}

		if (_enemy2->isActive())
		{
			if (_ship->collidesWith(_enemy2))
			{
				if (_ship->getX() < _enemy2->getX())
				{
					_ship->setVelocityX(abs(_ship->getVelocityX()) * -1);
					_enemy2->setVelocityX(abs(_enemy2->getVelocityX()));
				}
				else
				{
					_ship->setVelocityX(abs(_ship->getVelocityX()));
					_enemy2->setVelocityX(abs(_enemy2->getVelocityX()) * -1);
				}
				if (_ship->getY() < _enemy2->getY())
				{
					_ship->setVelocityY(abs(_ship->getVelocityY()) * -1);
					_enemy2->setVelocityY(abs(_enemy2->getVelocityY()));
				}
				else
				{
					_ship->setVelocityY(abs(_ship->getVelocityY()));
					_enemy2->setVelocityY(abs(_enemy2->getVelocityY()) * -1);
				}
			}
		}

		if (_ship->hitpoints <= 0)
		{
			_ship->setActive(false);
		}
		if (_enemy->hitpoints <= 0)
		{
			_enemy->setActive(false);
		}
		if (_enemy2->hitpoints <= 0)
		{
			_enemy2->setActive(false);
		}
	}

	void render()
	{
		_laser->render();
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