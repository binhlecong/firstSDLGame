#pragma once
#include "SDL.h"
#include "ColliderComponent.h"

class Collision
{
public:
	Collision() = default;
	~Collision() = default;

	static bool AABB(const SDL_Rect& rectA, const SDL_Rect& rectB);
	static bool AABB(const ColliderComponent& collA, const ColliderComponent& collB);
};