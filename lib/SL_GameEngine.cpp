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

void SL_GameEngine::setBackground(Uint8 red, Uint8 green, Uint8 blue)
{
	SDL_SetRenderDrawColor(_renderer, red, green, blue, 255);
}

void SL_GameEngine::setGameController(SL_GameController *gameController)
{
	_gameController = gameController;
	_gameController->setGameEngine(this);
}

void SL_GameEngine::run()
{
	if(_gameController != NULL)
	{
		_gameController->beforeRun();
	}
	while (_isRunning)
	{
		startLoop();

		handleEvents();
		update();
		render();

		endLoop();
	}

	if(_gameController != NULL)
	{
		_gameController->afterRun();
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
		if(_gameController != NULL)
		{
			_gameController->handleEvent(event);
		}

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
	if(_gameController != NULL)
	{
		_gameController->beforeUpdate();
	}

	// ...

	if(_gameController != NULL)
	{
		_gameController->afterUpdate();
	}
}

void SL_GameEngine::render()
{
	if(_gameController != NULL)
	{
		_gameController->beforeRender();
	}

	SDL_RenderClear(_renderer);

	if(_gameController != NULL)
	{
		_gameController->startRender();
	}

	// ...

	if(_gameController != NULL)
	{
		_gameController->endRender();
	}

	SDL_RenderPresent(_renderer);

	if(_gameController != NULL)
	{
		_gameController->afterRender();
	}
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
		printf("SL_GameEngine: frameDelay %d frameTime %d; frame takes to long to build\n", _frameDelay, _frameTime);
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