#include <SDL2/SDL.h>

#include "SL_GameEngine.h"
#include "SL_TextureManager.h"
#include "SL_GameObject.h"

const int GOT_PLAYER = 1;
const int GOT_LASER = 2;
const int GOT_ENEMY = 3;

class Laser : public SL_GameObject
{
public:
	void update()
	{
		SL_GameObject::update();

		if (getY() < 0 - (getHeight() / 2.0))
		{
			dispose();
		}

		for(unsigned int i = 0; i < getEngine()->gameObjects.size(); i++)
		{
			SL_GameObject *gameObject = getEngine()->gameObjects[i];
			if(collidesWith(gameObject))
			{
				if(gameObject->tag == GOT_ENEMY)
				{
					gameObject->hitpoints -= 10;
					dispose();
				}
			}
		}
	}
};

class Ship : public SL_GameObject
{
public:
	void update()
	{
		SL_GameObject::update();

		if (getX() - (getWidth() / 2.0) < 0)
		{
			setVelocityX(getVelocityX() * -1);
			setX(getWidth() / 2.0);
		}
		if (getX() + (getWidth() / 2.0) > getEngine()->getWidth())
		{
			setVelocityX(getVelocityX() * -1);
			setX(getEngine()->getWidth() - (getWidth() / 2.0));
		}
		if (getY() - (getHeight() / 2.0) < 0)
		{
			setVelocityY(getVelocityY() * -1);
			setY(getHeight() / 2.0);
		}
		if (getY() + (getHeight() / 2.0) > getEngine()->getHeight())
		{
			setVelocityY(getVelocityY() * -1);
			setY(getEngine()->getHeight() - (getHeight() / 2.0));
		}
	}
};

class Player : public Ship
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
			if (event.key.keysym.scancode == SDL_SCANCODE_SPACE)
			{
				fireLaser();
			}
			break;
		}
	}

	void fireLaser()
	{
		Laser *laser = new Laser();
		laser->setup("assets/laserRed03.png", getEngine()->getRenderer(), -100, -100, 4, 18);
		laser->setVelocityY(-300.0);
		laser->setXY(getX(), getY() - (getHeight() / 2.0) - (laser->getHeight() / 2.0));
		laser->setActive(true);
		laser->tag = GOT_LASER;

		getEngine()->addGameObject(laser);
	}
};

class Enemy : public Ship
{
public:
	void update()
	{
		Ship::update();

		if(hitpoints < 0)
		{
			dispose();
		}

		for(unsigned int i = 0; i < getEngine()->gameObjects.size(); i++)
		{
			SL_GameObject *gameObject = getEngine()->gameObjects[i];
			if(collidesWith(gameObject))
			{
				if(gameObject->tag == GOT_PLAYER)
				{
					gameObject->hitpoints -= 2;
					hitpoints -= 2;
					if (gameObject->getX() < getX())
					{
						gameObject->setVelocityX(abs(gameObject->getVelocityX()) * -1);
						setVelocityX(abs(getVelocityX()));
					}
					else
					{
						gameObject->setVelocityX(abs(gameObject->getVelocityX()));
						setVelocityX(abs(getVelocityX()) * -1);
					}
					if (gameObject->getY() < getY())
					{
						gameObject->setVelocityY(abs(gameObject->getVelocityY()) * -1);
						setVelocityY(abs(getVelocityY()));
					}
					else
					{
						gameObject->setVelocityY(abs(gameObject->getVelocityY()));
						setVelocityY(abs(getVelocityY()) * -1);
					}
				}
			}
		}
	}
};

class MyGameEngine : public SL_GameEngine
{
public:
	void initGameState()
	{
		Player *ship = new Player();
		ship->setup("assets/playerShip2_red.png", getRenderer(), (getWidth() / 2.0), (getHeight() / 2.0), 56, 36);
		ship->hitpoints = 20;
		ship->tag = GOT_PLAYER;
		addGameObject(ship);

		Enemy *enemy = new Enemy();
		enemy->setup("assets/enemyBlue3.png", getRenderer(), 100, 50, 51, 41);
		enemy->setVelocityX(220.0);
		enemy->setVelocityY(80.0);
		enemy->hitpoints = 35;
		enemy->tag = GOT_ENEMY;
		addGameObject(enemy);

		Enemy *enemy2 = new Enemy();
		enemy2->setup("assets/enemyBlue4.png", getRenderer(), getWidth() - 100, 80, 41, 42);
		enemy2->setVelocityX(-60.0);
		enemy2->setVelocityY(90.0);
		enemy2->hitpoints = 45;
		enemy2->tag = GOT_ENEMY;
		addGameObject(enemy2);
	}
};

int main()
{
	MyGameEngine *engine = new MyGameEngine();

	if (engine->setup("My Example Game", 640, 480, false, 30) == 0)
	{
		engine->initGameState();
		engine->setBackground(32, 32, 32);

		engine->run();

		engine->teardown();
	}

	delete engine;

	return 0;
}