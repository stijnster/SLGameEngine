#include <SDL2/SDL.h>

#include <SL_GameEngine.h>

class MyGameEngine : public SL_GameEngine
{
	void afterSetup()
	{
		printf("after setup called!\n");
	}

	void beforeUpdate()
	{
		printf("MyGameEngine::beforeUpdate\n");
	}

	void afterUpdate()
	{
		printf("MyGameEngine::afterUpdate\n");
	}

	void beforeRender()
	{
		printf("MyGameEngine::beforeRender\n");
	}

	void afterRender()
	{
		printf("MyGameEngine::afterRender\n");
	}

	void beforeTeardown()
	{
		printf("MyGameEngine::beforeTeardown\n");
	}

};

int main()
{
	MyGameEngine *engine = new MyGameEngine();

	if (engine->setup("My Example Game", 640, 480, false, 30) == 0)
	{
		engine->run();
		engine->teardown();
	}

	delete engine;

	return 0;
}