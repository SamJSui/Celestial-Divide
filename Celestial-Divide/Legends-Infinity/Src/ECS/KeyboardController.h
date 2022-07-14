#pragma once

#include "../Game.h"
#include "ECS.h"
#include "Components.h"

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
					sprite->setTex("assets/slime_behind.png");
					break;
				case SDLK_a:
				case SDLK_LEFT:
					transform->velocity.x = -1;
					sprite->setTex("assets/slime_left.png");
					break;
				case SDLK_d:
				case SDLK_RIGHT:
					transform->velocity.x = 1;
					sprite->setTex("assets/slime_right.png");
					break;
				case SDLK_s:
				case SDLK_DOWN:
					transform->velocity.y = 1;
					break;
				default:
					break;
			}
		}

		if (Game::event.type == SDL_KEYUP) {
			switch (Game::event.key.keysym.sym) {
			case SDLK_w:
			case SDLK_DOWN:
				transform->velocity.y = 0;
				sprite->setTex("assets/slime.png");
				break;
			case SDLK_a:
			case SDLK_LEFT:
				transform->velocity.x = 0;
				sprite->setTex("assets/slime.png");
				break;
			case SDLK_d:
			case SDLK_RIGHT:
				transform->velocity.x = 0;
				sprite->setTex("assets/slime.png");
				break;
			case SDLK_s:
			case SDLK_UP:
				transform->velocity.y = 0;
				sprite->setTex("assets/slime.png");
				break;
			default:
				break;
			}
		}
	}
private:
};
