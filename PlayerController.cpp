#include "PlayerController.h"
PlayerController::PlayerController() {
	OnCreate();
	this->playerTransform = nullptr;
	this->playerSprite = nullptr;
	this->controllableComponent = nullptr;
	this->cameraTransform = nullptr;
	this->cameraComponent = nullptr;
	previousMousePosition = sf::Mouse::getPosition();
}
PlayerController::PlayerController(Entity* player, Camera& camera) {
	OnCreate();
	this->playerTransform = player->getComponent<TransformComponent>();
	this->playerSprite = player->getComponent<SpriteComponent>();
	this->controllableComponent = player->getComponent<ControllableComponet>();
	this->cameraTransform = camera.getComponent<TransformComponent>();
	this->cameraComponent = camera.getComponent<CameraComponent>();
}
void PlayerController::OnCreate(){
}
void PlayerController::OnUpdate(float deltaTime){
	sf::Vector2i currentMousePosition = sf::Mouse::getPosition();
	sf::Vector2i deltaMousePosition = currentMousePosition - previousMousePosition;
	previousMousePosition = currentMousePosition;
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
				sf::rotate(this->playerTransform->rotation, this->controllableComponent->turnAngle * deltaTime);
				sf::rotate(this->cameraTransform->rotation, this->controllableComponent->turnAngle * deltaTime);
				sf::rotate(this->cameraComponent->plane, this->controllableComponent->turnAngle * deltaTime);
			}
			else if (sf::Keyboard::isKeyPressed(keyBinds[Keybinds::LOOK_LEFT])) {
				sf::rotate(this->playerTransform->rotation, -this->controllableComponent->turnAngle * deltaTime);
				sf::rotate(this->cameraTransform->rotation, -this->controllableComponent->turnAngle * deltaTime);
				sf::rotate(this->cameraComponent->plane, -this->controllableComponent->turnAngle * deltaTime);
			}

			if (sf::getLength(velocity) > this->controllableComponent->maxSpeed) {
				velocity = sf::getNormalized(velocity) * this->controllableComponent->maxSpeed;
			}
			//Move
			if (sf::Keyboard::isKeyPressed(keyBinds[Keybinds::SPRINT])) {
				playerTransform->position += velocity * (this->controllableComponent->sprintMultiplier * deltaTime);
				cameraTransform->position += velocity * (this->controllableComponent->sprintMultiplier * deltaTime);
			}
			else {
				playerTransform->position += velocity * (this->controllableComponent->movementMultiplier * deltaTime);
				cameraTransform->position += velocity * (this->controllableComponent->movementMultiplier * deltaTime);
			}
			//Update sprite
			playerSprite->sprite.setPosition(playerTransform->position);
			playerSprite->sprite.setRotation(sf::getRotationAngle(playerTransform->rotation));
			//Update Camera
			//if(camera!=nullptr)
			//{
			//	camera->setPosition(this->playerTransform->position);
			//	camera->setAngleDEG(sf::getRotationAngle(this->playerTransform->rotation));
			//}
		}
	}
}
void PlayerController::OnRender(){ }
void PlayerController::OnFixedUpdate(float fixedDeltaTime){}
void PlayerController::OnDestroy(){}

void PlayerController::setKeyBind(Keybinds key, sf::Keyboard::Key key_code){}
void PlayerController::setSensitivity(float sensitivity){}
void PlayerController::setPlayer(Entity* player, Camera& camera) {
	this->playerTransform = player->getComponent<TransformComponent>();
	this->playerSprite = player->getComponent<SpriteComponent>();
	this->controllableComponent = player->getComponent<ControllableComponet>();
	this->cameraTransform = camera.getComponent<TransformComponent>();
	this->cameraComponent = camera.getComponent<CameraComponent>();
}
void PlayerController::setMovementMultiplier(float movementMultiplier) {
	this->controllableComponent->movementMultiplier = movementMultiplier;
}
float PlayerController::getSensitivity() { return this->controllableComponent->sensitivity; };