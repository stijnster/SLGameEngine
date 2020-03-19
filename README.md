# SLGameEngine

## What is it?

The SLGameEngine is an attempt to develop a simple Game Engine. During a period of home schooling, I'm trying to teach my kids to program. With this engine, I want them to be able to create simple games with as little knowledge of C/C++ as possible. Then, with each iteration, we'll add more complexity in the actual game code.

[SDL2](https://www.libsdl.org/) seems like a great, cross-platform choice for game engine development. But it still requires some knowledge of C/C++ and programming in general. For my kids, it would take a couple of lessons/weeks to get to a point where a simple window would appear.

That's why I want decided to start the `SLGameEngine` which will wrap some functionality in simple calls.

## What is required?

In order to make a game, you'll need to include `SLGameEngine` into your project. You'll also need [SDL2](https://www.libsdl.org/) and [SDL2_image](https://www.libsdl.org/projects/SDL_image/).

### On the Mac

Do the following to install the requirements to your Mac;

```
brew install sdl2
brew install sdl2_image
```

## Example

Here is an example to setup, run and teardown an engine with a dark gray background color;

```cpp
#include "SL_GameEngine.h"

int main()
{
	SL_GameEngine *engine = new SL_GameEngine();

	// create a 800x640 window (not fullscreen) with a framerate of 25 frames per second
	if (engine->setup("My Example Game", 800, 640, false, 25) == 0)
	{
		// set the window background color (RGB values)
		engine->setBackground(127, 127, 127);

		// run the engine untill the user wants to quit
		engine->run();

		// tear down the engine
		engine->teardown();
	}

	delete engine;

	return 0;
}
```

Have a look in the example directory. It contains a working example of the engine and a Makefile to build the project.

## Credits

In the example project I've included assets from [Space Shooter (Redux, plus fonts and sounds) by Kenney Vleugels (www.kenney.nl)](https://www.kenney.nl/).
