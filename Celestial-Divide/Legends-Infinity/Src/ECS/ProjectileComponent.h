#pragma once

#include "ECS.h"
#include "Components.h"
#include "../Vector2D.h"

class ProjectileComponent : public Component {
public:
	ProjectileComponent(int rng, int sp, Vector2D vel) : range(rng), speed(sp), velocity(vel) {

	}
	~ProjectileComponent(){}

	void init() override {
		transform = &entity->getComponent<TransformComponent>();
		transform->velocity = velocity;
	}

	void update() override {
		distance += speed;

		if (distance > range) { 
			entity->destroy();
			std::cout << "Out of Range\n";
		}
		else if (transform->position.x > Game::camera.x + Game::camera.w ||
			transform->position.x < Game::camera.x ||
			transform->position.y > Game::camera.y + Game::camera.h ||
			transform->position.y < Game::camera.y) 
		{
			std::cout << "Out of Bounds\n";
			entity->destroy();
		}
	}
private:
	TransformComponent* transform;

	int range;
	int speed;
	int distance;
	Vector2D velocity;
};