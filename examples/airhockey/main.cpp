#include <SDL2/SDL.h>

#include <SL_GameEngine.h>

class Puck : public SL_GameObject
{
};

class Border : public SL_GameObject
{
};

class MyGameEngine : public SL_GameEngine
{
	Puck *puck;
	Border *topBorder, *leftBorder, *rightBorder, *bottomBorder;

	void setupBorders()
	{
		topBorder = new Border();
		topBorder->setup("assets/border.png", getRenderer(), getWidth() / 2.0, 8, getWidth(), 16);
		addGameObject(topBorder);
		leftBorder = new Border();
		leftBorder->setup("assets/border.png", getRenderer(), 8, getHeight() / 2.0, 16, getHeight());
		addGameObject(leftBorder);
		bottomBorder = new Border();
		bottomBorder->setup("assets/border.png", getRenderer(), getWidth() / 2.0, getHeight() - 8, getWidth(), 16);
		addGameObject(bottomBorder);
		rightBorder = new Border();
		rightBorder->setup("assets/border.png", getRenderer(), getWidth() - 8, getHeight() / 2.0, 16, getHeight());
		addGameObject(rightBorder);
	}

	void afterSetup()
	{
		setupBorders();

		puck = new Puck();
		puck->setup("assets/puck.png", getRenderer(), getWidth() / 2.0, getHeight() / 2.0, 64, 64);
		puck->setVelocityX(1000.0);
		puck->setVelocityY(1000.0);
		addGameObject(puck);
	}

	void afterUpdate()
	{
		if (puck->collidesWith(bottomBorder))
		{
			puck->setY(bottomBorder->getY() - (bottomBorder->getHeight() / 2.0) - (puck->getHeight() / 2.0) - 1);
			puck->setVelocityY(puck->getVelocityY() * -1);
		}
		if(puck->collidesWith(topBorder))
		{
			puck->setY(topBorder->getY() + (topBorder->getHeight() / 2.0) + (puck->getHeight() / 2.0) + 1);
			puck->setVelocityY(puck->getVelocityY() * -1);
		}
		if (puck->collidesWith(leftBorder))
		{
			puck->setX(leftBorder->getX() + (leftBorder->getWidth() / 2.0) + (puck->getWidth() / 2.0) + 1);
			puck->setVelocityX(puck->getVelocityX() * -1);
		}
		if (puck->collidesWith(rightBorder))
		{
			puck->setX(rightBorder->getX() - (rightBorder->getWidth() / 2.0) - (puck->getWidth() / 2.0) - 1);
			puck->setVelocityX(puck->getVelocityX() * -1);
		}
	}
};

int main()
{
	MyGameEngine *engine = new MyGameEngine();

	if (engine->setup("My Example Game", 1024, 768, false, 60) == 0)
	{
		engine->run();
		engine->teardown();
	}

	delete engine;

	return 0;
}