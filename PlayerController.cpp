#include "PlayerController.h"
PlayerController::PlayerController() {
	OnCreate();
	this->playerTransform = nullptr;
	this->playerSprite = nullptr;
	this->controllableComponent = nullptr;
	this->colliderComponent = nullptr;
	this->camera = nullptr;
}
PlayerController::PlayerController(Entity* player, Camera& camera) {
	OnCreate();
	this->playerTransform = player->getComponent<TransformComponent>();
	this->controllableComponent = player->getComponent<ControllableComponet>();
	this->colliderComponent = player->getComponent<ColliderComponent>();
	this->camera = &camera;
}
void PlayerController::OnCreate(){
	previousMousePosition = sf::Mouse::getPosition();
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
			right = sf::getRotated(right, -90);
			sf::Vector2f velocity(0, 0);

			if (sf::Keyboard::isKeyPressed(keyBinds[Keybinds::FORWARDS]))
				velocity += forward;
			else if (sf::Keyboard::isKeyPressed(keyBinds[Keybinds::BACKWARDS]))
				velocity += (forward * -1.0f);
			
			if (sf::Keyboard::isKeyPressed(keyBinds[Keybinds::RIGHT]))
				velocity += right;
			else if (sf::Keyboard::isKeyPressed(keyBinds[Keybinds::LEFT]))
				velocity += (right * -1.0f);
			
			if (sf::Keyboard::isKeyPressed(keyBinds[Keybinds::LOOK_RIGHT]))
				sf::rotate(this->playerTransform->rotation, -this->controllableComponent->turnAngle * deltaTime);
			else if (sf::Keyboard::isKeyPressed(keyBinds[Keybinds::LOOK_LEFT]))
				sf::rotate(this->playerTransform->rotation, this->controllableComponent->turnAngle * deltaTime);

			if (sf::Keyboard::isKeyPressed(keyBinds[Keybinds::LOOK_UP]))
				this->camera->setZHeight(this->camera->getZHeight() + 0.01f);
			else if (sf::Keyboard::isKeyPressed(keyBinds[Keybinds::LOOK_DOWN]))
				this->camera->setZHeight(this->camera->getZHeight() - 0.01f);

			if (sf::getLength(velocity) > this->controllableComponent->maxSpeed) {
				velocity = sf::getNormalized(velocity) * this->controllableComponent->maxSpeed;
			}
			//Move
			if (sf::Keyboard::isKeyPressed(keyBinds[Keybinds::SPRINT]))
				playerTransform->position += velocity * (this->controllableComponent->sprintMultiplier * deltaTime);
			else
				playerTransform->position += velocity * (this->controllableComponent->movementMultiplier * deltaTime);
			colliderComponent->border.top = this->playerTransform->position.y - (colliderComponent->border.height / 2);
			colliderComponent->border.left = this->playerTransform->position.x - (colliderComponent->border.width / 2);

			camera->setPosition(playerTransform->position);
			camera->setRotation(playerTransform->rotation);
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
	this->camera = &camera;
}
void PlayerController::setMovementMultiplier(float movementMultiplier) {
	this->controllableComponent->movementMultiplier = movementMultiplier;
}
float PlayerController::getSensitivity() { return this->controllableComponent->sensitivity; };