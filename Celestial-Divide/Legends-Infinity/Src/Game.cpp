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

std::vector<ColliderComponent*> Game::colliders;

bool Game::isRunning = false;

auto& player(manager.addEntity());
auto& wall(manager.addEntity());

const char* mapfile = "assets/terrain_ss.png";

enum groupLabels : std::size_t {
	groupMap,
	groupPlayers,
	groupEnemies,
	groupColliders
};

auto& tiles(manager.getGroup(groupMap));
auto& players(manager.getGroup(groupPlayers));
auto& enemies(manager.getGroup(groupEnemies));

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
	Map::LoadMap("assets/map.map", 25, 20);

	player.addComponent<TransformComponent>( 3);
	player.addComponent<SpriteComponent>("assets/player_anims.png", true);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);
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

	Vector2D pVel = player.getComponent<TransformComponent>().velocity;
	int pSpeed = player.getComponent<TransformComponent>().speed;

	for (auto t : tiles) {
		t->getComponent<TileComponent>().destRect.x += -(pVel.x * pSpeed);
		t->getComponent<TileComponent>().destRect.y += -(pVel.y * pSpeed);
	}
}

// RENDERER
void Game::render() {
	SDL_RenderClear(renderer);
	for (auto& t : tiles) { // TILES
		t->draw();
	}
	for (auto& p : players) { // PLAYERS
		p->draw();
	}
	for (auto& e : enemies) { // ENEMIES
		e->draw();
	}
	SDL_RenderPresent(renderer);
}

// CLEAN
void Game::clean() {
	delete(map);
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned!...";
}

void Game::AddTile(int srcX, int srcY, int xpos, int ypos) {
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(srcX, srcY, xpos, ypos, mapfile);
	tile.addGroup(groupMap);
}
