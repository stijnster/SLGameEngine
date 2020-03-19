#include "../lib/SL_GameEngine.h"

SL_GameEngine *engine;

int main()
{
	engine = new SL_GameEngine();

	delete engine;

	return 0;
}