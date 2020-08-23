#pragma once
// handle entities' appearance 

#include "SDL.h"
#include "Components.h"
#include "TextureManager.h"	
#include "TransformComponent.h"
#include "Animation.h"
#include <map>

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
	int animIndex = 0;

	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

	std::map<const char*, Animation> animations;

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

	SpriteComponent(const char* path, bool isAnimated)
	{
		animated = isAnimated;

		setTexture(path);

		Animation idle = Animation(0, 3, 200);
		Animation walk = Animation(1, 8, 200);

		animations.emplace("Idle", idle);
		animations.emplace("Walk", walk);

		srcRect.x = srcRect.y = 0;
		srcRect.w = srcRect.h = 0;

		desRect.x = desRect.y = 0;
		desRect.w = desRect.h = 0;

		Play("Idle");
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

		srcRect.y = srcRect.h * animIndex;

		desRect.x = static_cast<int>(transform->position.x);
		desRect.y = static_cast<int>(transform->position.y);

		desRect.w = transform->width * transform->scale;
		desRect.h = transform->height * transform->scale;
	}

	void draw() override
	{
		TextureManager::Draw(texture ,srcRect, desRect, spriteFlip);
	}

	void Play(const char* animName)
	{
		frames = animations[animName].frames;
		animIndex = animations[animName].index;
		speed = animations[animName].speed;
	}
};