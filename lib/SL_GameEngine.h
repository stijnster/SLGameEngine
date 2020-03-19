#ifndef SL_GAMEENGINE_H
#define SL_GAMEENGINE_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include "SL_GameController.h"

class SL_GameEngine
{
private:
	SDL_Window *_window;
	SDL_Renderer *_renderer;
	SL_GameController *_gameController;

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
	 * Sets the game controller
	 *
	 * The game controller can be used as a callback class to receive events from the engine.
	 */
	void setGameController(SL_GameController *gameController);

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
	SDL_Renderer *getRenderer(){ return _renderer; };
};

#endif