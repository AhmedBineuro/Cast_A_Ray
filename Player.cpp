#include "Player.h"
Player::Player(entt::registry* registry) :Entity2D(registry){
	this->addComponent(ControllableComponet());
	this->controllable = this->getComponent<ControllableComponet>();
	this->camera = new Camera(registry,this->transformComponent->position);
	this->addComponent(ScriptComponent(std::make_shared <PlayerController>(this->transformComponent, this->spriteComponent, this->controllable, this->camera)));
}
Player::Player(entt::registry* registry, sf::Vector2f position) :Entity2D(registry,position) {
	this->addComponent(ControllableComponet());
	this->controllable = this->getComponent<ControllableComponet>();
	this->camera = new Camera(registry, this->transformComponent->position);
	this->addComponent(ScriptComponent(std::make_shared <PlayerController>(this->transformComponent, this->spriteComponent, this->controllable,this->camera)));
}
void Player::setPosition(sf::Vector2f position) const{
	this->transformComponent->position = position;
	this->spriteComponent->sprite.setPosition(position);
	this->camera->setPosition(this->transformComponent->position);
}
Player::~Player() {
	free(camera);
}