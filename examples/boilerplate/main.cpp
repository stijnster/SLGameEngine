#include <SDL2/SDL.h>

#include <SL_GameEngine.h>

class MyGameEngine : public SL_GameEngine
{
};

int main()
{
	MyGameEngine *engine = new MyGameEngine();

	if (engine->setup("My Example Game", 640, 480, false, 30) == 0)
	{
		engine->run();
	}

	delete engine;

	return 0;
}