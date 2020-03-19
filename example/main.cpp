#include "SL_GameEngine.h"

int main()
{
	SL_GameEngine *engine = new SL_GameEngine();

	if(engine->setup("My Example Game", 800, 640, false, 25) == 0)
	{
		engine->setBackground(127, 127, 127);

		engine->run();
		engine->teardown();
	}

	delete engine;

	return 0;
}