#include "Entity2D.h"
#include "Resource_Manager.h"
Entity2D::Entity2D(entt::registry* registry):Entity(registry){
	this->addComponent(RenderComponent());
	this->addComponent(SpriteComponent());
	this->addComponent(TransformComponent());
	
	this->renderComponent = (this->getComponent<RenderComponent>());
	this->spriteComponent = (this->getComponent<SpriteComponent>());
	this->transformComponent = (this->getComponent<TransformComponent>());
	this->transformComponent->rotation = sf::Vector2f(1, 0);
	//Sprite setup
	Resource_Manager& rm = Resource_Manager::getResourceManager();
	ResourceLoadingInfo rli;
	rli.name = "Casta";
	rli.type = "texture";
	rli.URL = "./casta.png";
	rm.loadResource(rli);
	this->setSpriteTexture(rm.getTexture("Casta"));
	this->size = sf::Vector2f(1, 1);
	setSize(size);
	this->spriteComponent->sprite.setPosition(400, 400);
	sf::Vector2u textSize = this->spriteComponent->sprite.getTexture()->getSize();
	this->spriteComponent->sprite.setOrigin((float)textSize.x / 2.0f, (float)textSize.y / 2.0f);
	setEnabled(true);
}
Entity2D::Entity2D(entt::registry* registry, sf::Vector2f position):Entity2D(registry){
	this->transformComponent = this->getComponent<TransformComponent>();
	SpriteComponent* spriteComponent = this->getComponent<SpriteComponent>();
	transformComponent->position = position;
	spriteComponent->sprite.setPosition(position);
}

void Entity2D::setPosition(sf::Vector2f position) const {
	this->transformComponent->position = position;
	this->spriteComponent->sprite.setPosition(position);
}

void Entity2D::setSpriteTexture(sf::Texture& texture){
	this->spriteComponent->sprite.setTexture(texture);
	sf::Vector2u textSize = texture.getSize();
	sf::Vector2f scale(size.x / (float)textSize.x, size.y / (float)textSize.y);
	this->spriteComponent->sprite.setScale(scale);
	this->spriteComponent->sprite.setOrigin((float)textSize.x / 2.0f, (float)textSize.y / 2.0f);
}
void Entity2D::setEnabled(bool value){
	this->renderComponent->enabled = value;
}
void Entity2D::setRenderStates(sf::RenderStates renderStates){
	this->renderComponent->renderStates = renderStates;
}

void Entity2D::setSize(sf::Vector2f newSize) {
	sf::Vector2u size = this->spriteComponent->sprite.getTexture()->getSize();
	sf::Vector2f scale(newSize.x / (float)size.x, newSize.y / (float)size.y);
	this->spriteComponent->sprite.setScale(scale);
	this->size.x = newSize.x;
	this->size.y = newSize.y;
}