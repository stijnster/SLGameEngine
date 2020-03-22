#include "SL_GameObject.h"
#include "SL_TextureManager.h"

SL_GameObject::SL_GameObject()
{
}

SL_GameObject::~SL_GameObject()
{
}

void SL_GameObject::setup(const char *filename, SDL_Renderer *renderer, int x, int y, int width, int height)
{
	_renderer = renderer;

	SL_TextureWidthAndHeight textureManagerWidthAndHeight = SL_TextureManager::loadTextureWithAndHeight(filename, _renderer);

	_texture = textureManagerWidthAndHeight.texture;

	_velocityX = 0.0;
	_velocityY = 0.0;

	_sourceRect.x = 0;
	_sourceRect.y = 0;
	_sourceRect.w = textureManagerWidthAndHeight.w;
	_sourceRect.h = textureManagerWidthAndHeight.h;

	_x = x;
	_y = y;
	_width = width;
	_height = height;

	_dispose = false;
	_active = true;
	_ticksSinceLastUpdate = SDL_GetTicks();

	hitpoints = 0;

	_updatePosition();
}

void SL_GameObject::teardown()
{
	if (_texture != NULL)
	{
		SL_TextureManager::destroyTexture(_texture);
	}
}

void SL_GameObject::setSourceRect(int x, int y, int w, int h)
{
	_sourceRect.x = x;
	_sourceRect.y = y;
	_sourceRect.w = w;
	_sourceRect.h = h;
}

void SL_GameObject::setActive(bool active)
{
	_active = active;
}

void SL_GameObject::setXY(int x, int y)
{
	_x = x;
	_y = y;
	_updatePosition();
}

void SL_GameObject::setX(int x)
{
	setXY(x, getY());
}

void SL_GameObject::setY(int y)
{
	setXY(getX(), y);
}

void SL_GameObject::setWidth(int width)
{
	_width = width;
	_updatePosition();
}

void SL_GameObject::setHeight(int height)
{
	_height = height;
	_updatePosition();
}

void SL_GameObject::_updatePosition()
{
	_destinationRect.x = round(_x - (_width / 2.0));
	_destinationRect.y = round(_y - (_height / 2.0));
	_destinationRect.w = _width;
	_destinationRect.h = _height;
}

void SL_GameObject::handleEvent(SDL_Event event)
{
}

void SL_GameObject::update()
{
	if (_active)
	{
		float _ticks = (SDL_GetTicks() - _ticksSinceLastUpdate) / 1000.0;

		if (_velocityX != 0.0)
		{
			setX(_x + (_velocityX * _ticks));
		}

		if (_velocityY != 0.0)
		{
			setY(_y + (_velocityY * _ticks));
		}
	}

	_ticksSinceLastUpdate = SDL_GetTicks();
}

void SL_GameObject::render()
{
	if (_active)
	{
		SDL_RenderCopy(_renderer, _texture, &_sourceRect, &_destinationRect);
	}
}

void SL_GameObject::dispose()
{
	_dispose = true;
}

bool SL_GameObject::shouldBeDisposed()
{
	return _dispose;
}


SDL_Rect SL_GameObject::getColliderRect()
{
	return _destinationRect;
}

bool SL_GameObject::collidesWith(SL_GameObject *object)
{
	SDL_Rect self = this->getColliderRect();
	SDL_Rect other = object->getColliderRect();

	bool collisionX = (((self.x + self.w) >= other.x) && ((other.x + other.w) >= self.x));
	bool collisionY = (((self.y + self.h) >= other.y) && ((other.y + other.h) >= self.y));

	return collisionX && collisionY;
}

void SL_GameObject::setEngine(SL_GameEngine *engine){
	_engine = engine;
}