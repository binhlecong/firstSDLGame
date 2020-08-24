#include "Map.h"
#include "Game.h"
#include "TextureManager.h"
#include "Components.h"
#include "Collision.h"

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
std::vector<ColliderComponent*> Game::colliders;

Manager manager;

auto& newPlayer(manager.addEntity());

enum groupLabels :std::size_t
{
	groupMap,
	groupPlayers,
	groupEnemies,
	groupColliders
};

Game::Game()
{
	count = 0;
	isRunning = true;
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

	//map = new Map();

	// ECS
	Map::loadMap("Assets/map32_20_1.txt", 32, 20);

	newPlayer.addComponent<TransformComponent>();
	newPlayer.addComponent<SpriteComponent>("Assets/player_anims.png", true);
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
	manager.refresh();
	manager.update();

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

auto& tiles(manager.getGroup(groupMap));
auto& players(manager.getGroup(groupPlayers));
auto& enemies(manager.getGroup(groupEnemies));

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

void Game::addTile(int x, int y, int id)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(x, y, 32, 32, id);
	tile.addGroup(groupMap);
}