#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* texture) {
	// SDL_Surface* tmpSurface = IMG_Load(texture);
	// SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
	// SDL_FreeSurface(tmpSurface);
	SDL_Texture* tex = IMG_LoadTexture(Game::renderer, texture);
	return tex;
}

void TextureManager::Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest) {
	SDL_RenderCopy(Game::renderer, tex, &src, &dest);
}