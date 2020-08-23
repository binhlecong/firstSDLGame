#pragma once
// handle entities' appearance 

#include "SDL.h"
#include "Components.h"
#include "TextureManager.h"	
#include "TransformComponent.h"

class SpriteComponent : public Component
{
private:
	SDL_Texture* texture;
	SDL_Rect srcRect, desRect;
	TransformComponent* transform;

	bool animated = false;
	int frames = 0;
	int speed = 100;

public:
	SpriteComponent() = default;

	~SpriteComponent()
	{
		std::cout << "<<< Sprite texture destroyed! ..." << std::endl;
		SDL_DestroyTexture(texture);
	}

	SpriteComponent(const char* path)
	{
		setTexture(path);

		srcRect.x = srcRect.y = 0;
		srcRect.w = srcRect.h = 0;

		desRect.x = desRect.y = 0;
		desRect.w = desRect.h = 0;
	}

	SpriteComponent(const char* path, int mFrames, int mSpeed)
	{
		setTexture(path);

		srcRect.x = srcRect.y = 0;
		srcRect.w = srcRect.h = 0;

		desRect.x = desRect.y = 0;
		desRect.w = desRect.h = 0;

		animated = true;
		frames = mFrames;
		speed = mSpeed;
	}

	void setTexture(const char* path)
	{
		texture = TextureManager::loadTexture(path);
	}

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = transform->width;
		srcRect.h = transform->height;
	}

	void update() override
	{
		if (animated)
		{
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
		}

		desRect.x = static_cast<int>(transform->position.x);
		desRect.y = static_cast<int>(transform->position.y);

		desRect.w = transform->width * transform->scale;
		desRect.h = transform->height * transform->scale;
	}

	void draw() override
	{
		TextureManager::Draw(texture ,srcRect, desRect);
	}
};