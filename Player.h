#pragma once
#include"Entity2D.h"
#include "PlayerController.h"
#include "Camera.h"
class Player :public Entity2D {
public:
	Player(entt::registry* registry);
	Player(entt::registry* registry, sf::Vector2f position);
	void setPosition(sf::Vector2f position) const override;
	Camera* camera;
	~Player();
protected:
	ControllableComponet* controllable;
};
