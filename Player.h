#pragma once
#include"Entity2D.h"
#include "PlayerController.h"
#include "Camera.h"
class Player :public Entity {
public:
	Player(entt::registry* registry);
	Player(entt::registry* registry, sf::Vector2f position);
	void draw(sf::RenderTarget& canvas, sf::Vector2f tileSize);
	void setSpriteTexture(sf::Texture& texture);
	void setPosition(sf::Vector2f position);
	void setSpriteSize(sf::Vector2f newSize);
	Camera* camera;
	~Player();
protected:
	ControllableComponent* controllable;
	ColliderComponent* colliderComponent;
	SpriteComponent* spriteComponent;
	TransformComponent* transformComponent;
	sf::Vector2f spriteSize;
};
