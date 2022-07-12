#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"

Map* map;
Manager manager;	

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
auto& player(manager.addEntity());

Game::Game() {

}
Game::~Game() {

}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
		width = 1920;
		height = 1080;
	}

	// INIT
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Subsystems Initialized!...\n";

		// WINDOW
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window) {
			std::cout << "Window Created!...\n";
		}

		// RENDERER
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
			std::cout << "Renderer Created!...\n";
		}
		
		isRunning = true;
	}
	else {
		isRunning = false;
	}
	
	// MAP INSTANTIATION
	map = new Map();

	// ECS
	player.addComponent<TransformComponent>();
	player.addComponent<SpriteComponent>("assets/player.gif");
	player.addComponent<KeyboardController>();
}

// EVENT HANDLER
void Game::handleEvents() {
	SDL_PollEvent(&event);

	switch (event.type) {
		case SDL_QUIT:
			isRunning = false;
			break;
		default:
			break;
	}

}

// UPDATE
void Game::update() {
	manager.refresh();
	manager.update();
	if (player.getComponent<TransformComponent>().position.x < 100) {
		player.getComponent<SpriteComponent>().setTex("assets/enemy.gif");
	}
	else {
		player.getComponent<SpriteComponent>().setTex("assets/player.gif");
	}
}

// RENDERER
void Game::render() {
	SDL_RenderClear(renderer);
	map->DrawMap();
	manager.draw();
	SDL_RenderPresent(renderer);
}

// CLEAN
void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned!...";
}
