#pragma once

#include "ECS.h"
#include "Vector2D.h"
#include "Game.h"
#include "TextureManager.h"

class TileComponent : public Component
{
public:

	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
	Vector2D position;

	TileComponent() = default;

	~TileComponent()
	{
		std::cout << "<<< Tile texture destroyed! ..." << std::endl;
		SDL_DestroyTexture(texture);
	}

	TileComponent(int xpos, int ypos, int tsize, int tscale, int id)
	{
		texture = TextureManager::loadTexture("Assets/terrain_ss.png");

		srcRect.x = id % 10 * tsize;
		srcRect.y = id / 10 * tsize;
		srcRect.w = srcRect.h = tsize;
		position.x = static_cast<float>(xpos);
		position.y = static_cast<float>(ypos);
		destRect.w = destRect.h = tsize * tscale;
	}

	void update() override
	{
		destRect.x = static_cast<int>(position.x - Game::camera.x);
		destRect.y = static_cast<int>(position.y - Game::camera.y);
	}

	void draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
	}
};