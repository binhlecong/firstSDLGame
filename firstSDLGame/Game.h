#ifndef Game_h
#define Game_h

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <math.h>
#include <vector>

class ColliderComponent;

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int x, int y, int width, int height, bool fullScreen);
	
	void handleEvent();
	void update();
	void render();
	void clean();
	bool running() { return isRunning; }

	// Only one game renderer, so we will declare it as static 
	static void addTile(int x, int y, int id);
	static SDL_Renderer* renderer;
	static SDL_Event event;
	static std::vector<ColliderComponent*> colliders;
	static bool isRunning;
	static SDL_Rect camera;

private:
	int count = 0;
	// need use pointers
	SDL_Window* window; 
};

#endif // !Game_h


