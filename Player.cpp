#include "Player.h"
Player::Player(entt::registry* registry) :Entity2D(registry){
	this->addComponent(ControllableComponet());
	this->transformComponent->rotation = sf::Vector2f(1, 0);
	this->controllable = this->getComponent<ControllableComponet>();
	this->camera = new Camera(registry,this->transformComponent->position, this->transformComponent->rotation);
	this->addComponent(ScriptComponent(std::make_shared <PlayerController>(this, *(this->camera))));
}
Player::Player(entt::registry* registry, sf::Vector2f position) :Entity2D(registry,position) {
	this->addComponent(ControllableComponet());
	this->transformComponent->rotation = sf::Vector2f(1, 0);
	this->controllable = this->getComponent<ControllableComponet>();
	this->camera = new Camera(registry, this->transformComponent->position, this->transformComponent->rotation);
	this->addComponent(ScriptComponent(std::make_shared <PlayerController>(this,*(this->camera))));
}
void Player::setPosition(sf::Vector2f position) const{
	this->transformComponent->position = position;
	this->spriteComponent->sprite.setPosition(position);
	this->camera->setPosition(this->transformComponent->position);
}
Player::~Player() {
	free(camera);
}