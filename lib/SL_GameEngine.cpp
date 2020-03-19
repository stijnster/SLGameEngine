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

void SL_GameEngine::run()
{
	while (_isRunning)
	{
		startLoop();

		handleEvents();
		update();
		render();

		endLoop();
	}
}

void SL_GameEngine::startLoop()
{
	_frameStart = SDL_GetTicks();
}

void SL_GameEngine::handleEvents()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			_isRunning = false;
			break;
		default:
			break;
		}
	}
}

void SL_GameEngine::update()
{
	// ...
}

void SL_GameEngine::render()
{
	SDL_RenderClear(_renderer);

	// ...

	SDL_RenderPresent(_renderer);
}

void SL_GameEngine::endLoop()
{
	_frameTime = SDL_GetTicks() - _frameStart;
	if (_frameDelay > _frameTime)
	{
		SDL_Delay(_frameDelay - _frameTime);
	}
	else
	{
		printf("frameDelay %d frameTime %d; frame takes to long to build\n", _frameDelay, _frameTime);
	}
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