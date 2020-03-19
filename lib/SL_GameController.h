#ifndef SL_GAMECONTROLLER_H
#define SL_GAMECONTROLLER_H

#include <SDL2/SDL.h>
#include "SL_GameEngine.h"

class SL_GameEngine;

class SL_GameController
{
protected:
	SL_GameEngine *_gameEngine;

public:
	void setGameEngine(SL_GameEngine *gameEngine) { _gameEngine = gameEngine; };
	virtual void beforeRun() {};
	virtual void afterRun() {};
	virtual void handleEvent(SDL_Event event) {};
	virtual void beforeUpdate() {};
	virtual void afterUpdate() {};
	virtual void beforeRender() {};
	virtual void startRender() {};
	virtual void endRender() {};
	virtual void afterRender() {};
};

#endif
