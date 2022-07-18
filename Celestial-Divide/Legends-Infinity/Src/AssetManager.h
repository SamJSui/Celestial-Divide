#pragma once

#include <map>
#include <string>
#include "TextureManager.h"
#include "Vector2D.h"
#include "ECS/ECS.h"

class AssetManager {
public:
	AssetManager(Manager* man);
	~AssetManager();

	// GAME OBJECTS
	void CreateProjectile(Vector2D pos, Vector2D vel, int range, int speed, std::string id);

	// TEXTURE MANAGEMENT
	void AddTexture(std::string, const char* path);
	SDL_Texture* GetTexture(std::string id);
private:
	Manager* manager;
	std::map<std::string, SDL_Texture*> textures;
};