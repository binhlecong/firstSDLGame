#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "string"

class Map
{
public:
	Map(const char* mfp, int ms, int ts);
	~Map();

	void loadMap(const std::string& path, int sizeX, int sizeY);
	void addTile(int x, int y, int id);

private:
	const char* mapFilePath;
	int mapScale;
	int tileSize;
};

