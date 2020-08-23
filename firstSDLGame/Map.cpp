#include "Map.h"
#include "Game.h"
#include "TextureManager.h"
#include "BitmapData.h"
#include <string>
#include <fstream>

Map::Map()
{}

Map::~Map()
{}

void Map::loadMap(const std::string& path, int sizeX, int sizeY)
{
	char tile;
	std::ifstream mapFile;
	mapFile.open(path);

	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			mapFile.get(tile);
			Game::addTile(x * 32, y * 32, atoi(&tile));
			mapFile.ignore();
		}
	}

	mapFile.close();
}