#include "Map.h"
#include "Game.h"
#include "TextureManager.h"
#include "Components.h"
#include "ECS.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>

// use manager object declared in line 14 of Game.cpp
extern Manager manager;

Map::Map(const char* mfp, int ms, int ts) :
	mapFilePath(mfp), mapScale(ms), tileSize(ts)
{

}

Map::~Map()
{}

void Map::loadMap(const std::string& path, int sizeX, int sizeY)
{
	int scaledSize = tileSize * mapScale;

	std::ifstream mapFile;
	mapFile.open(path);

	std::string line;
	for (int y = 0; y < sizeY; y++)
	{
		std::getline(mapFile, line);
		std::vector<int> v;
		std::stringstream ss(line);

		int cnt = 0;
		for (int i; ss >> i;) {
			v.push_back(i);
			if (ss.peek() == ',')
				ss.ignore();
			cnt++;
		}

		for (int x = 0; x < sizeX; x++)
		{
			addTile(x * scaledSize, y * scaledSize, v[x]);
			std::cout << std::setfill('0') << std::setw(2) << v[x] << ' ';
		}
		std::cout << std::endl;
	}

	mapFile.ignore();

	for (int y = 0; y < sizeY; y++)
	{
		std::getline(mapFile, line);
		std::vector<int> v;
		std::stringstream ss(line);

		for (int i; ss >> i;) {
			v.push_back(i);
			if (ss.peek() == ',')
				ss.ignore();
		}

		for (int x = 0; x < sizeX; x++)
		{
			if (v[x] == 1)
			{
				auto& tcol(manager.addEntity());
				tcol.addComponent<ColliderComponent>("terrain", 
					x * scaledSize, y * scaledSize, scaledSize);
				tcol.addGroup(Game::groupColliders);
			}
			std::cout << v[x] << ' ';
		}
		std::cout << std::endl;
	}

	mapFile.close();
}

void Map::addTile(int x, int y, int id)
{
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(x, y, 32, 2, id);
	tile.addGroup(Game::groupMap);
}