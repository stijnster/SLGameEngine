#ifndef SL_GAMEOBJECT_H
#define SL_GAMEOBJECT_H

#include <SDL2/SDL.h>

class SL_GameObject
{
public:
	SL_GameObject(const char *filename, SDL_Renderer *renderer, int x, int y, int width, int height);
	~SL_GameObject();

	void setSourceRect(int x, int y, int w, int h);
	void setX(int x);
	int getX() { return _x; };

	void setY(int y);
	int getY() { return _y; };

	void setXY(int x, int y);

	void setWidth(int width);
	int getWidth() { return _width; };

	void setHeight(int height);
	int getHeight() { return _height; };

	void update();
	void render();

private:
	int _x;
	int _y;
	int _width;
	int _height;
	SDL_Texture *_texture;
	SDL_Renderer *_renderer;
	SDL_Rect _sourceRect, _destinationRect;

	void _updatePosition();
};

#endif