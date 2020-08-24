#pragma once
#include "ECS.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "SDL.h"

class TileComponent : public Component
{
public:
	TransformComponent* transform;
	SpriteComponent* sprite;

	SDL_Rect tileRect;
	SDL_Rect _srcRect;
	int tileID;
	char* path;

	TileComponent() = default;

	TileComponent(int x, int y, int h, int w, int id)
	{
		tileRect.x = x;
		tileRect.y = y;
		tileRect.h = h;
		tileRect.w = w;
		path = NULL;
		transform = NULL;
		sprite = NULL;

		tileID = id;
		path = _strdup("Assets/terrain_ss.png");
		_srcRect.h = _srcRect.w = 32;
		_srcRect.y = id / 10 * 32;
		_srcRect.x = id % 10 * 32;
		/*switch (tileID)
		{
		case 0:
			path = _strdup("Assets/dirt.png");
			break;
		case 1:
			path = _strdup("Assets/grass.png");
			break;
		case 2:
			path = _strdup("Assets/water.png");
			break;
		case 3:
			path = _strdup("Assets/sand.png");
			break;
		case 4:
			path = _strdup("Assets/rock.png");
			break;
		default:
			break;
		}*/
	}

	void init() override
	{
		entity->addComponent<TransformComponent>(tileRect.x, tileRect.y, tileRect.h, tileRect.w, 2);
		transform = &entity->getComponent<TransformComponent>();

		entity->addComponent<SpriteComponent>(path, false, _srcRect);
		sprite = &entity->getComponent<SpriteComponent>();
	}
};