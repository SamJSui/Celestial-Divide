#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"

Map* map;
Manager manager;	

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
auto& player(manager.addEntity());
auto& wall(manager.addEntity());

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
	player.addComponent<SpriteComponent>("assets/slime.png");
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");

	wall.addComponent<TransformComponent>(300.0, 300.0, 300, 20, 1);
	wall.addComponent<SpriteComponent>("assets/old/rock.png");
	wall.addComponent<ColliderComponent>("wall");
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
	if (Collision::AABB(player.getComponent<ColliderComponent>().collider, wall.getComponent<ColliderComponent>().collider)) {
		player.getComponent<TransformComponent>().scale = 1;
		player.getComponent<TransformComponent>().velocity * -1;
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
