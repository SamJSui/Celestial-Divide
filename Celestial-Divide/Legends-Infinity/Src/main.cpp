#include "Game.h"
#include <climits>
#include <chrono>

Game* game = nullptr;

int main(int argc, char **argv) {	
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	game = new Game();
	game->init("Celestial Divide", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false);

	while (game->running()) {
		auto start = std::chrono::steady_clock::now();
		game->handleEvents();
		game->update();
		game->render();
		auto end = std::chrono::steady_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;
		if (frameDelay > elapsed_seconds.count()) {
			SDL_Delay(frameDelay - elapsed_seconds.count());
		}
	}

	game->clean();

	return 0;
}