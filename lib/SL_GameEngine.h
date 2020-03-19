#ifndef SL_GAMEENGINE_H
#define SL_GAMEENGINE_H

#include <stdio.h>
#include <SDL2/SDL.h>

class SL_GameEngine
{
private:
	SDL_Window *_window;
	SDL_Renderer *_renderer;

	int _FPS, _frameDelay, _frameTime;
	Uint32 _frameStart;
	bool _isRunning;

	void startLoop();
	void handleEvents();
	void update();
	void render();
	void endLoop();

public:
	SL_GameEngine();
	~SL_GameEngine();

	int setup(const char *title, int width, int height, bool fullscreen, int fps);
	void setBackground(Uint8 red, Uint8 green, Uint8 blue);
	void run();
	void teardown();
};

#endif