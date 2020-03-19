#ifndef SL_GAMEENGINE_H
#define SL_GAMEENGINE_H

#include <stdio.h>
#include <SDL2/SDL.h>

class SL_GameEngine
{
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
	void _render();
	void _endLoop();

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

	/**
	 * Handle a single event
	 *
	 * Events in the game loop are pulled and passed on to this virtual function.
	 *
	 * @param event The event to handle
	 */
	virtual void handleEvent(SDL_Event event);

	/**
	 * Update derived GameEngine
	 *
	 * A virtual function for the derived GameEngine that can is called from the game loop during the _update phase.
	 */
	virtual void update();

	/**
	 * Render derived GameEngine
	 *
	 * A virtual function for the derived GameEngine that can is called from the game loop during the _render phase.
	 */
	virtual void render();
};

#endif