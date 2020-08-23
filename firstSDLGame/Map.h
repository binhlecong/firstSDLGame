#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "string"

class Map
{
public:
	Map();
	~Map();

	static void loadMap(const std::string& path, int sizeX, int sizeY);
};

