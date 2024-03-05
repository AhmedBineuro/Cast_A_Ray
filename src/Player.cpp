#include "Player.h"
Player::Player(entt::registry* registry) :Entity2D(registry){
	this->addComponent(ControllableComponet());
	this->transformComponent->rotation = sf::Vector2f(1, 0);
	this->controllable = this->getComponent<ControllableComponet>();
	this->camera = new Camera(registry,this->transformComponent->position, this->transformComponent->rotation);
	this->addComponent(ScriptComponent(std::make_shared <PlayerController>(this, *(this->camera))));
	this->addComponent(ColliderComponent(transformComponent->position, sf::Vector2f(1, 1)));
	colliderComponent = this->getComponent<ColliderComponent>();
}
Player::Player(entt::registry* registry, sf::Vector2f position) :Entity2D(registry,position) {
	this->addComponent(ControllableComponet());
	this->transformComponent->rotation = sf::Vector2f(1, 0);
	this->controllable = this->getComponent<ControllableComponet>();
	this->camera = new Camera(registry, this->transformComponent->position, this->transformComponent->rotation);
	this->addComponent(ScriptComponent(std::make_shared <PlayerController>(this,*(this->camera))));
	this->addComponent(ColliderComponent(transformComponent->position, sf::Vector2f(1, 1)));
	colliderComponent = this->getComponent<ColliderComponent>();
}
void Player::setPosition(sf::Vector2f position) const{
	this->transformComponent->position = position;
	this->spriteComponent->sprite.setPosition(position);
	this->camera->setPosition(this->transformComponent->position);
	this->colliderComponent->border.top = this->transformComponent->position.y - (this->colliderComponent->border.height/2);
	this->colliderComponent->border.left = this->transformComponent->position.x - (this->colliderComponent->border.width / 2);
}
Player::~Player() {
	free(camera);
}