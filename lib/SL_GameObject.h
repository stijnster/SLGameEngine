#ifndef SL_GAMEOBJECT_H
#define SL_GAMEOBJECT_H

#include <SDL2/SDL.h>

class SL_GameObject
{
public:
	int hitpoints;

	SL_GameObject();
	~SL_GameObject();

	void setup(const char *filename, SDL_Renderer *renderer, int x, int y, int width, int height);
	void teardown();

	void setSourceRect(int x, int y, int w, int h);
	SDL_Rect getColliderRect();

	void setActive(bool active);
	bool isActive() { return _active; };

	void setX(int x);
	int getX() { return _x; };

	void setY(int y);
	int getY() { return _y; };

	void setXY(int x, int y);

	void setWidth(int width);
	int getWidth() { return _width; };

	void setHeight(int height);
	int getHeight() { return _height; };

	void setVelocityX(float velocityX) { _velocityX = velocityX; };
	float getVelocityX() { return _velocityX; };
	void setVelocityY(int velocityY) { _velocityY = velocityY; };
	float getVelocityY() { return _velocityY; };

	void update();
	void render();

	bool collidesWith(SL_GameObject *object);

private:
	int _x;
	int _y;
	int _width;
	int _height;
	float _velocityX;
	float _velocityY;
	bool _active;

	SDL_Texture *_texture;
	SDL_Renderer *_renderer;
	SDL_Rect _sourceRect, _destinationRect;
	Uint32 _ticksSinceLastUpdate;

	void _updatePosition();
};

#endif