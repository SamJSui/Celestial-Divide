#pragma once

#include "Components.h"
#include "../Vector2D.h"

class TransformComponent : public Component {
public:
	Vector2D position;

	TransformComponent() {
		position.x = 0.0;
		position.y = 0.0;
	}

	TransformComponent(float x, float y) {
		position.x = x;
		position.y = y;
	}
	void update() override {
		position.x++;
		position.y++;
	}
	int x() { return position.x; }
	void x(int x) { position.x = x; }
	int y() { return position.y; }
	void y(int y) { position.y = y; }
	void setPos(int x, int y) {
		position.x = x;
		position.y = y;
	}
};