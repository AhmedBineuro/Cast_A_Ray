#include "Player.h"

Player::Player(entt::registry* registry) :Entity2D(registry) {
	this->addComponent(ScriptComponent(std::make_shared <PlayerController>(this->transformComponent, this->spriteComponent)));
	this->addComponent(ControllableComponet());
	this->controllable = this->getComponent<ControllableComponet>();
}
Player::Player(entt::registry* registry, sf::Vector2f position) :Entity2D(registry,position) {
	this->addComponent(ScriptComponent(std::make_shared <PlayerController>(this->transformComponent, this->spriteComponent)));
	this->addComponent(ControllableComponet());
	this->controllable = this->getComponent<ControllableComponet>();
}
void Player::setPosition(sf::Vector2f position) const{
	this->transformComponent->position = position;
	this->spriteComponent->sprite.setPosition(position);
}