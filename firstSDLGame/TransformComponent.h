#pragma once
// handle entity movement, position

#include "Components.h"
#include "Vector2D.h"

class TransformComponent : public Component
{
public:
	Vector2D position;
	Vector2D velocity;
	int speed = 2;
	int scale = 1;

	int height = 32;
	int width  = 32;

	TransformComponent()
	{
		position.setZero();
	}

	TransformComponent(float x, float y)
	{
		position.x = x;
		position.y = y;
	}

	TransformComponent(int scl)
	{
		position.setZero();
		position.x = 512;
		position.y = 320;
		scale = scl;
	}

	TransformComponent(float x, float y, int h, int w, int scl)
	{
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		scale = scl;
	}

	void init() override
	{ 
		velocity.setZero();
	}

	void update() override
	{
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}
};