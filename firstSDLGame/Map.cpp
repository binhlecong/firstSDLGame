#include "Map.h"
#include "Game.h"
#include "TextureManager.h"
#include "BitmapData.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>

Map::Map()
{}

Map::~Map()
{}

void Map::loadMap(const std::string& path, int sizeX, int sizeY)
{
	std::ifstream mapFile;
	mapFile.open(path);

	std::string line;
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
			Game::addTile(x * 32, y * 32, v[x]);
			std::cout << std::setfill('0') << std::setw(2) << v[x] << ' ';
		}
		std::cout << std::endl;
		/*for (int x = 0; x < sizeX; x++)
		{
			mapFile.get(tile);
			Game::addTile(x * 32, y * 32, atoi(&tile));
			mapFile.ignore();
		}*/
	}

	mapFile.close();
}