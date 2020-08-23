#pragma once
// handle collision between entities

#include "SDL.h"
#include "Components.h"
#include <string>

class ColliderComponent : public Component
{
public:
	// Axis-Aligned Bounding Box ( AABB )
	SDL_Rect colliderRect;
	std::string tag;
	TransformComponent* transform;

	ColliderComponent(std::string t)
	{
		tag = t; 
	}

	void init() override
	{
		if (!entity->hasComponent<TransformComponent>())
		{
			&entity->addComponent<TransformComponent>();
		}
		transform = &entity->getComponent<TransformComponent>();

		Game::colliders.push_back(this);
	}

	void update() override
	{
		colliderRect.x = (int)transform->position.x;
		colliderRect.y = (int)transform->position.y;

		colliderRect.w = transform->width * transform->scale;
		colliderRect.h = transform->height * transform->scale;
	}
};