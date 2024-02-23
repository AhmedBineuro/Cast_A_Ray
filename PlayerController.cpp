#include "PlayerController.h"
PlayerController::PlayerController() {
	OnCreate();
	this->playerTransform = nullptr;
	this->playerSprite = nullptr;
}
PlayerController::PlayerController(TransformComponent* playerTransform, SpriteComponent* playerSprite, ControllableComponet* controllableComponent) {
	OnCreate();
	this->playerTransform = playerTransform;
	this->playerSprite = playerSprite;
	this->controllableComponent = controllableComponent;
}
void PlayerController::OnCreate(){
	std::cout << "Player Controller on create!" << std::endl;
}
void PlayerController::OnUpdate(float deltaTime){
	if (playerTransform != nullptr && playerSprite != nullptr&& controllableComponent != nullptr)
	{
		if(this->controllableComponent->enabled)
		{
			sf::Vector2f forward = this->playerTransform->rotation * this->controllableComponent->maxSpeed;
			sf::Vector2f right = this->playerTransform->rotation * this->controllableComponent->maxSpeed;
			right = sf::getRotated(right, 90);
			sf::Vector2f velocity(0, 0);

			if (sf::Keyboard::isKeyPressed(keyBinds[Keybinds::FORWARDS]))
			{
				velocity += forward;
			}
			else if (sf::Keyboard::isKeyPressed(keyBinds[Keybinds::BACKWARDS]))
			{
				velocity += (forward * -1.0f);
			}
			if (sf::Keyboard::isKeyPressed(keyBinds[Keybinds::RIGHT]))
			{
				velocity += right;
			}
			else if (sf::Keyboard::isKeyPressed(keyBinds[Keybinds::LEFT]))
			{
				velocity += (right * -1.0f);
			}
			if (sf::Keyboard::isKeyPressed(keyBinds[Keybinds::LOOK_RIGHT]))
			{
				sf::rotate(this->playerTransform->rotation, -this->controllableComponent->turnAngle * deltaTime);
			}
			else if (sf::Keyboard::isKeyPressed(keyBinds[Keybinds::LOOK_LEFT])) {
				sf::rotate(this->playerTransform->rotation, this->controllableComponent->turnAngle * deltaTime);
			}

			if (sf::getLength(velocity) > this->controllableComponent->maxSpeed) {
				velocity = sf::getNormalized(velocity) * this->controllableComponent->maxSpeed;
			}
			if (sf::Keyboard::isKeyPressed(keyBinds[Keybinds::SPRINT])) {
				playerTransform->position += velocity * (this->controllableComponent->sprintMultiplier * deltaTime);
			}
			else {
				playerTransform->position += velocity * (this->controllableComponent->movementMultiplier * deltaTime);
			}
			playerTransform->position += velocity * (this->controllableComponent->movementMultiplier * deltaTime);
			playerSprite->sprite.setPosition(playerTransform->position);

			playerSprite->sprite.setRotation(sf::getRotationAngle(playerTransform->rotation));
		}
	}
}
void PlayerController::OnRender(){ }
void PlayerController::OnFixedUpdate(float fixedDeltaTime){}
void PlayerController::OnDestroy(){}

void PlayerController::setKeyBind(Keybinds key, sf::Keyboard::Key key_code){}
void PlayerController::setSensitivity(float sensitivity){}
void PlayerController::setPlayer(TransformComponent* playerTransform, SpriteComponent* playerSprite, ControllableComponet* controllableComponent) {
	this->playerTransform = playerTransform;
	this->playerSprite = playerSprite;
	this->controllableComponent = controllableComponent;
}
void PlayerController::setMovementMultiplier(float movementMultiplier) {
	this->controllableComponent->movementMultiplier = movementMultiplier;
}
float PlayerController::getSensitivity() { return this->controllableComponent->sensitivity; };