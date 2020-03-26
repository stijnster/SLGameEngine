#ifndef SL_GAMEENGINE_H
#define SL_GAMEENGINE_H

#include <stdio.h>
#include <vector>
#include <SDL2/SDL.h>

#include "SL_GameObject.h"

class SL_GameObject;

class SL_GameEngine
{
public:
	SL_GameEngine();
	~SL_GameEngine();

	std::vector<SL_GameObject *> gameObjects;

	/**
	 * Engine setup
	 *
	 * This sets up the engine with a window with name, a specified size and a given frame rate.
	 *
	 * @param title The name of the window (shown in the window title bar)
	 * @param width The width of the window
	 * @param height The height of the window
	 * @param fullscreen Show the window fullscreen
	 * @param fps The framerate to run the engine
	 * @return 0 when the setup was successfull, 1 if the setup failed
	 */
	int setup(const char *title, int width, int height, bool fullscreen, int fps);

	/**
	 * Set window background color
	 *
	 * Sets the background color on the renderer/window. The color is passed in as RGB values.
	 *
	 * @param red The value of the red color
	 * @param green The value of the green color
	 * @param green The value of the blue color
	 */
	void setBackground(Uint8 red, Uint8 green, Uint8 blue);

	/**
	 * Run the Engine
	 *
	 * Runs the engine untill the user wants to quit.
	 */
	void run();

	/**
	 * Teardown the engine
	 *
	 * This will clean up all created instances used by the engine.
	 */
	void teardown();

	/**
	 * Provides access to the renderer
	 */
	SDL_Renderer *getRenderer() { return _renderer; };

	/**
	 * Provides access to the GameEngine width
	 */
	int getWidth() { return _width; };

	/**
	 * Provides access to the GameEngine height
	 */
	int getHeight() { return _height; };

	int getMillisecondsSinceLastLoop() { return _millisecondsSinceLastLoop; }

	void addGameObject(SL_GameObject *gameObject);

	/**
	 * A hook that gets called when the engine has completed setup and is ready to run
	 */
	virtual void afterSetup(){};

	/**
	 * A hook that gets called to process a single event
	 *
	 * Events in the game loop are pulled and passed on to this virtual function.
	 *
	 * @param event The event to handle
	 */
	virtual void handleEvent(SDL_Event event){};

	/**
	 * A hook that gets called before update
	 */
	virtual void beforeUpdate(){};

	/**
	 * A hook that gets called after update
	 */
	virtual void afterUpdate(){};

	/**
	 * A hook that gets called before render
	 */
	virtual void beforeRender(){};

	/**
	 * A hook that gets called after render
	 */
	virtual void afterRender(){};

	/**
	 * A hook that gets called before teardown
	 */
	virtual void beforeTeardown(){};

private:
	SDL_Window *_window;
	SDL_Renderer *_renderer;

	int _width, _height;
	int _FPS, _frameDelay, _frameTime;
	int _millisecondsSinceLastLoop;
	Uint32 _frameStart;
	bool _isRunning;

	void _startLoop();
	void _handleEvents();
	void _update();
	void _garbageCollection();
	void _render();
	void _endLoop();
};

#endif