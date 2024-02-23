#include "PlayerController.h"
PlayerController::PlayerController() {
	OnCreate();
	this->playerTransform = nullptr;
	this->playerSprite = nullptr;
}
PlayerController::PlayerController(TransformComponent* playerTransform, SpriteComponent* playerSprite) {
	OnCreate();
	this->playerTransform = playerTransform;
	this->playerSprite = playerSprite;
}
void PlayerController::OnCreate(){
	std::cout << "Player Controller on create!" << std::endl;
}
void PlayerController::OnUpdate(float deltaTime){
	if (playerTransform != nullptr && playerSprite != nullptr)
	{
		sf::Vector2f forward = this->playerTransform->rotation * this->maxSpeed;
		sf::Vector2f right = this->playerTransform->rotation * this->maxSpeed;
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
			sf::rotate(this->playerTransform->rotation, -30.0f * deltaTime);
		}
		else if (sf::Keyboard::isKeyPressed(keyBinds[Keybinds::LOOK_LEFT])) {
			sf::rotate(this->playerTransform->rotation, 30.0f * deltaTime);
		}

		if (sf::Keyboard::isKeyPressed(keyBinds[Keybinds::SPRINT])) {
			this->movementMultiplier = 2.0f;
		}
		else {
			this->movementMultiplier = 1.0f;
		}
		if (sf::getLength(velocity) > maxSpeed) {
			velocity = sf::getNormalized(velocity) * maxSpeed;
		}
		playerTransform->position += velocity * (movementMultiplier * deltaTime);
		playerSprite->sprite.setPosition(playerTransform->position);

		playerSprite->sprite.setRotation(sf::getRotationAngle(playerTransform->rotation));
	}
}
void PlayerController::OnRender(){ }
void PlayerController::OnFixedUpdate(float fixedDeltaTime){}
void PlayerController::OnDestroy(){}

void PlayerController::setKeyBind(Keybinds key, sf::Keyboard::Key key_code){}
void PlayerController::setSensitivity(float sensitivity){}
void PlayerController::setPlayer(TransformComponent* playerTransform, SpriteComponent* playerSprite) {
	this->playerTransform = playerTransform;
	this->playerSprite = playerSprite;
}
void PlayerController::setMovementMultiplier(float movementMultiplier) {
	this->movementMultiplier = movementMultiplier;
}
float PlayerController::getSensitivity() { return this->sensitivity; };