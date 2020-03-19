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

	if(engine->setup("My Example Game", 800, 640, false, 25) == 0)
	{
		engine->setBackground(127, 127, 127);

		engine->run();
		engine->teardown();
	}

	delete engine;

	return 0;
}
```
