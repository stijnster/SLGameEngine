#include "SL_GameEngine.h"

SL_GameEngine::SL_GameEngine()
{
	printf("SL_GameEngine: Starts\n");

	_isRunning = false;
}

SL_GameEngine::~SL_GameEngine()
{
	printf("SL_GameEngine: Ends\n");
}

int SL_GameEngine::setup(const char *title, int width, int height, bool fullscreen, int fps)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		return 1;
	}

	_FPS = fps;
	_frameDelay = 1000 / _FPS;

	int flags = 0;
	if (fullscreen)
	{
		flags = flags | SDL_WINDOW_FULLSCREEN;
	}

	_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
	if (_window == NULL)
	{
		printf("SL_GameEngine: Unable to create window\n");
		return 1;
	}

	_renderer = SDL_CreateRenderer(_window, -1, 0);
	if (_renderer == NULL)
	{
		printf("SL_GameEngine: Unable to create renderer\n");
		return 1;
	}

	_isRunning = true;

	return 0;
}

void SL_GameEngine::teardown()
{
	if (_renderer)
	{
		SDL_DestroyRenderer(_renderer);
	}

	if (_window)
	{
		SDL_DestroyWindow(_window);
	}

	SDL_Quit();
}