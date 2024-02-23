#include "Player.h"

Player::Player(entt::registry* registry) :Entity2D(registry) {
	this->addComponent(ControllableComponet());
	this->controllable = this->getComponent<ControllableComponet>();
	this->addComponent(ScriptComponent(std::make_shared <PlayerController>(this->transformComponent, this->spriteComponent, this->controllable)));
}
Player::Player(entt::registry* registry, sf::Vector2f position) :Entity2D(registry,position) {
	this->addComponent(ControllableComponet());
	this->controllable = this->getComponent<ControllableComponet>();
	this->addComponent(ScriptComponent(std::make_shared <PlayerController>(this->transformComponent, this->spriteComponent, this->controllable)));
}
void Player::setPosition(sf::Vector2f position) const{
	this->transformComponent->position = position;
	this->spriteComponent->sprite.setPosition(position);
}