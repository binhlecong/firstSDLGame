#include "Game.h"

int main(int argc, char* argv[])
{
	Game* game = nullptr;

	const int FPS = 60;
	const int framedelay = 1000 / FPS;

	Uint32 frameStart = 0;
	int frameTime = 0;

	game = new Game();
	game->init("fisrtGame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 640, false);

	while (game->running())
	{
		// measure time from when SDL is int to now
		frameStart = SDL_GetTicks();
		// 1. handle user input
		game->handleEvent();
		// 2. update all object status
		game->update();
		// 3. render changes to the display
		game->render();
		// get the amount of time to delay
		frameTime = SDL_GetTicks() - frameStart;

		// delay frame if needed
		if (framedelay > frameTime)
		{
			SDL_Delay(framedelay - frameTime);
		}
		else std::cout << "!!! FPS dropped" << std::endl;
	}

	game->clean();

	return 0;
}