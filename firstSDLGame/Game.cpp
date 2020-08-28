#include "Map.h"
#include "Game.h"
#include "TextureManager.h"
#include "Components.h"
#include "Collision.h"

bool Game::isRunning = true;
SDL_Rect Game::camera = { 0, 0, 1024, 640 };

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

Map* map;
Manager manager;

auto& newPlayer(manager.addEntity());

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& enemies(manager.getGroup(Game::groupEnemies));
auto& colliders(manager.getGroup(Game::groupColliders));

Game::Game()
{
	count = 0;
	window = nullptr;
}

Game::~Game()
{
	std::cout << "<<< Game closed! ..." << std::endl;
}

void Game::init(const char* title, int x, int y, int width, int height, bool fullScreen)
{
	int flag = 0;
	if (fullScreen)
	{
		flag = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << ">>> Subsystem initilised! ..." << std::endl;

		window = SDL_CreateWindow(title, x, y, width, height, flag);
		if (window)
		{
			std::cout << ">>> Window created! ..." << std::endl;
		}

		Game::renderer = SDL_CreateRenderer(window, -1, 0);
		if (Game::renderer)
		{
			SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
			std::cout << ">>> Renderer created! ..." << std::endl;
		}

		isRunning = true;
	}
	else
	{
		isRunning = false;
	}

	map = new Map("Assets/terrain_ss.png", 2, 32);

	// ECS
	map->loadMap("Assets/map.map", 25, 20);

	SDL_Rect playerRect;
	playerRect.x = playerRect.y = playerRect.w = playerRect.h = 0;
	newPlayer.addComponent<TransformComponent>(400.0f, 320.0f, 32, 32, 2);
	newPlayer.addComponent<SpriteComponent>("Assets/player_anims.png", true, playerRect);
	newPlayer.addComponent<KeyboardController>();
	newPlayer.addComponent<ColliderComponent>("player");
	newPlayer.addGroup(groupPlayers);
}

void Game::handleEvent()
{
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;

	default:
		break;
	}
}

void Game::update()
{
	SDL_Rect playerCol = newPlayer.getComponent<ColliderComponent>().colliderRect;
	// get the position of the player before update so that we can force him 
	// back to that when collision occur.
	Vector2D playerOldPos = newPlayer.getComponent<TransformComponent>().position;

	manager.refresh();
	manager.update();

	for (auto& c : colliders)
	{
		SDL_Rect cCol = c->getComponent<ColliderComponent>().colliderRect;
		if (Collision::AABB(playerCol, cCol))
		{
			newPlayer.getComponent<TransformComponent>().position = playerOldPos;
		}
	}

	Vector2D plPosition = newPlayer.getComponent<TransformComponent>().position;

	// update the screen from which the camera will show
	camera.x = plPosition.x - 512;
	camera.y = plPosition.y - 320;
	camera.x = std::max(0, camera.x);
	camera.x = std::min(576, camera.x);
	camera.y = std::max(0, camera.y);
	camera.y = std::min(640, camera.y);

	// not a efficient method
	/*for (auto aTile : tiles)
	{
		aTile->getComponent<TileComponent>().sprite->desRect.x -= (plVelocity.x * plSpeed);
		aTile->getComponent<TileComponent>().transform->position.x -= (plVelocity.x * plSpeed);
		aTile->getComponent<TileComponent>().sprite->desRect.y -= (plVelocity.y * plSpeed);
		aTile->getComponent<TileComponent>().transform->position.y -= (plVelocity.y * plSpeed);
	}*/
	// temporary test
	/*for (auto cc : colliders)
	{
		ColliderComponent playerCollComp = newPlayer.getComponent<ColliderComponent>();
		if (Collision::AABB(playerCollComp, *cc) && cc != &playerCollComp)
		{
			newPlayer.getComponent<TransformComponent>().velocity * (1);
			std::cout << "hit" << std::endl;
		}
	}*/
}

void Game::render()
{
	// clear what is in the render biffer
	SDL_RenderClear(Game::renderer);
	for (auto& t : tiles)
	{
		t->draw();
	}

	for (auto& p : players)
	{
		p->draw();
	}

	for (auto& e : enemies)
	{
		e->draw();
	}

	/*for (auto& c : colliders)
	{
		c->draw();
	}*/
	// update the screen
	SDL_RenderPresent(Game::renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(Game::renderer);
	SDL_Quit();
	std::cout << "<<< Game cleared. Finished! ..." << std::endl;
}