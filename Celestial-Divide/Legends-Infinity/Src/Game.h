#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <stdio.h>
#include <iostream>

class Game {
public: 
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void handleEvents();
	void update();
	bool running() { return isRunning; }
	void render();
	void clean();

	static SDL_Renderer* renderer;
	static SDL_Event event;
private:
	int count = 0; 
	bool isRunning = false;
	SDL_Window* window;
};