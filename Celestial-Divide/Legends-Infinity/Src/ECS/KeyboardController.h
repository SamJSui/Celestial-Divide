#pragma once

#include "../Game.h"
#include "ECS.h"
#include "Components.h"
#include "../AssetManager.h"

class KeyboardController : public Component {
public:
	TransformComponent* transform;
	SpriteComponent* sprite;
	void init() override {
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();
	}
	void update() override {
		if (Game::event.type == SDL_KEYDOWN) { // DOWN ARROW
			switch (Game::event.key.keysym.sym) {
				case SDLK_w:
				case SDLK_UP:
					transform->velocity.y = -1;
					sprite->play("Walk");
					break;
				case SDLK_a:
				case SDLK_LEFT:
					transform->velocity.x = -1;
					sprite->play("Walk");
					sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
					break;
				case SDLK_d:
				case SDLK_RIGHT:
					transform->velocity.x = 1;
					sprite->play("Walk");
					break;
				case SDLK_s:
				case SDLK_DOWN:
					transform->velocity.y = 1;
					sprite->play("Walk");
					break;
				case SDLK_SPACE:
				default:
					break;
			}
		}

		if (Game::event.type == SDL_KEYUP) {
			switch (Game::event.key.keysym.sym) {
				case SDLK_w:
				case SDLK_DOWN:
					transform->velocity.y = 0;
					sprite->play("Idle");
					break;
				case SDLK_a:
				case SDLK_LEFT:
					transform->velocity.x = 0;
					sprite->play("Idle");
					sprite->spriteFlip = SDL_FLIP_NONE;
					break;
				case SDLK_d:
				case SDLK_RIGHT:
					transform->velocity.x = 0;
					sprite->play("Idle");
					break;
				case SDLK_s:
				case SDLK_UP:
					transform->velocity.y = 0;
					sprite->play("Idle");
					break;
				case SDLK_ESCAPE:
					Game::isRunning = false;
				case SDLK_SPACE:
					Game::assets->CreateProjectile(Vector2D((entity->getComponent<TransformComponent>().position.x + entity->getComponent<TransformComponent>().width * entity->getComponent<TransformComponent>().scale),
															entity->getComponent<TransformComponent>().position.y + entity->getComponent<TransformComponent>().height),
													Vector2D(2, 0), 200, 2, "projectile");
				default:
					break;
				}
		}
	}
private:
};
