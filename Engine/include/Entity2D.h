#pragma once
#include "Core\include\Entity.h"
#include "Core\include\Core.h"
#include "Engine\include\Actor.h"
class Entity2D:public Entity {
public:
	Entity2D(entt::registry* registry);
	Entity2D(entt::registry* registry,sf::Vector2f position);
	void setSpriteTexture(sf::Texture &texture);
	virtual void setPosition(sf::Vector2f position)const;
	void setSize(sf::Vector2f size);
	void setEnabled(bool value);
	void setRenderStates(sf::RenderStates renderStates);
protected:
	TransformComponent* transformComponent;
	RenderComponent* renderComponent;
	SpriteComponent* spriteComponent;
	sf::Vector2f size;
};