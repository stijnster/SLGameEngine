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

	_width = width;
	_height = height;

	_FPS = fps;
	_frameDelay = 1000 / _FPS;

	int flags = 0;
	if (fullscreen)
	{
		flags = flags | SDL_WINDOW_FULLSCREEN;
	}

	_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height, flags);
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

void SL_GameEngine::run()
{
	_millisecondsSinceLastLoop = 0;
	while (_isRunning)
	{
		_startLoop();

		_handleEvents();
		_update();
		_garbageCollection();
		_render();

		_endLoop();
	}
}

void SL_GameEngine::_startLoop()
{
	_frameStart = SDL_GetTicks();
}

void SL_GameEngine::_handleEvents()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		handleEvent(event);

		for (unsigned int i = 0; i < gameObjects.size(); i++)
		{
			gameObjects[i]->handleEvent(event);
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

void SL_GameEngine::_update()
{
	for (unsigned int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->update();
	}

	update();
}

void SL_GameEngine::_garbageCollection()
{
	for(unsigned int i = gameObjects.size(); i > 0; i--){
		SL_GameObject *gameObject = gameObjects[i - 1];
		if(gameObject->shouldBeDisposed())
		{
			gameObject->teardown();
			delete gameObject;

			gameObjects.erase(gameObjects.begin() + (i - 1));
		}
	}
}

void SL_GameEngine::_render()
{
	SDL_RenderClear(_renderer);

	for (unsigned int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->render();
	}
	render();

	SDL_RenderPresent(_renderer);
}

void SL_GameEngine::_endLoop()
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
	_millisecondsSinceLastLoop = SDL_GetTicks() - _frameStart;
}

void SL_GameEngine::teardown()
{
	for (unsigned int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->dispose();
	}
	_garbageCollection();

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

void SL_GameEngine::addGameObject(SL_GameObject *gameObject)
{
	gameObject->setEngine(this);
	gameObjects.push_back(gameObject);
}

void SL_GameEngine::handleEvent(SDL_Event event)
{
}

void SL_GameEngine::update()
{
}

void SL_GameEngine::render()
{
}
