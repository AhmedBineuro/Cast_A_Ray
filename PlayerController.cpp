#include "PlayerController.h"
PlayerController::PlayerController() {
	OnCreate();
	this->playerTransform = nullptr;
	this->playerSprite = nullptr;
	this->controllableComponent = nullptr;
	this->colliderComponent = nullptr;
	this->camera = std::weak_ptr<Camera>();
}
PlayerController::PlayerController(Entity* player, Camera* camera) {
	OnCreate();
	this->playerTransform = player->getComponent<TransformComponent>();
	this->controllableComponent = player->getComponent<ControllableComponent>();
	this->colliderComponent = player->getComponent<ColliderComponent>();
	this->camera = std::weak_ptr(std::shared_ptr<Camera>(camera));
}
void PlayerController::OnCreate(){
	previousMousePosition = sf::Mouse::getPosition();
}
void PlayerController::OnUpdate(float deltaTime){
	sf::Vector2i currentMousePosition = sf::Mouse::getPosition();
	sf::Vector2i deltaMousePosition = currentMousePosition - previousMousePosition;
	previousMousePosition = currentMousePosition;
	std::shared_ptr<Camera> cam = this->camera.lock();
	if (playerTransform != nullptr && playerSprite != nullptr && controllableComponent != nullptr)
	{
		if (this->controllableComponent->enabled)
		{
			sf::Vector2f forward = this->playerTransform->rotation * this->controllableComponent->maxSpeed;
			sf::Vector2f right = this->playerTransform->rotation * this->controllableComponent->maxSpeed;
			right = sf::getRotated(right, -90);
			if (keyStates[Keybinds::FORWARDS])
				velocity += forward;
			else if (keyStates[Keybinds::BACKWARDS])
				velocity += (forward * -1.0f);

			if (keyStates[Keybinds::RIGHT])
				velocity += right;
			else if (keyStates[Keybinds::LEFT])
				velocity += (right * -1.0f);
			if(sf::Keyboard::isKeyPressed(keyBinds[Keybinds::SPRINT]))
				velocity = velocity * (this->controllableComponent->sprintMultiplier * deltaTime);
			else
				velocity = velocity * (this->controllableComponent->movementMultiplier * deltaTime);

			if (keyStates[Keybinds::LOOK_RIGHT])
				sf::rotate(this->playerTransform->rotation, -this->controllableComponent->turnAngle * deltaTime);
			else if (keyStates[Keybinds::LOOK_LEFT])
				sf::rotate(this->playerTransform->rotation, this->controllableComponent->turnAngle * deltaTime);
			if (cam != nullptr && keyStates[Keybinds::LOOK_UP])
				cam->setZHeight(cam->getZHeight() + 0.01f);
			else if (cam != nullptr && keyStates[Keybinds::LOOK_DOWN])
				cam->setZHeight(cam->getZHeight() - 0.01f);
		}

		if (sf::getLength(velocity) > this->controllableComponent->maxSpeed) {
			velocity = sf::getNormalized(velocity) * this->controllableComponent->maxSpeed;
		}
		playerTransform->position += velocity * (this->controllableComponent->movementMultiplier * deltaTime);
		colliderComponent->border.top = this->playerTransform->position.y - (colliderComponent->border.height / 2);
		colliderComponent->border.left = this->playerTransform->position.x - (colliderComponent->border.width / 2);

		if (!cam)
			return;
		cam->setPosition(playerTransform->position);
		cam->setRotation(playerTransform->rotation);
	}
}
	//sf::Vector2i currentMousePosition = sf::Mouse::getPosition();
	//sf::Vector2i deltaMousePosition = currentMousePosition - previousMousePosition;
	//previousMousePosition = currentMousePosition;
	//std::shared_ptr<Camera> cam = this->camera.lock();
	//if (playerTransform != nullptr && playerSprite != nullptr&& controllableComponent != nullptr)
	//{
	//	if(this->controllableComponent->enabled)
	//	{
	//		sf::Vector2f forward = this->playerTransform->rotation * this->controllableComponent->maxSpeed;
	//		sf::Vector2f right = this->playerTransform->rotation * this->controllableComponent->maxSpeed;
	//		right = sf::getRotated(right, -90);
	//		sf::Vector2f velocity(0, 0);

	//		if (sf::Keyboard::isKeyPressed(keyBinds[Keybinds::FORWARDS]))
	//			velocity += forward;
	//		else if (sf::Keyboard::isKeyPressed(keyBinds[Keybinds::BACKWARDS]))
	//			velocity += (forward * -1.0f);
	//		
	//		if (sf::Keyboard::isKeyPressed(keyBinds[Keybinds::RIGHT]))
	//			velocity += right;
	//		else if (sf::Keyboard::isKeyPressed(keyBinds[Keybinds::LEFT]))
	//			velocity += (right * -1.0f);
	//		
	//		if (sf::Keyboard::isKeyPressed(keyBinds[Keybinds::LOOK_RIGHT]))
	//			sf::rotate(this->playerTransform->rotation, -this->controllableComponent->turnAngle * deltaTime);
	//		else if (sf::Keyboard::isKeyPressed(keyBinds[Keybinds::LOOK_LEFT]))
	//			sf::rotate(this->playerTransform->rotation, this->controllableComponent->turnAngle * deltaTime);

	//		if (cam!= nullptr  && sf::Keyboard::isKeyPressed(keyBinds[Keybinds::LOOK_UP]))
	//			cam->setZHeight(cam->getZHeight() + 0.01f);
	//		else if (cam != nullptr  && sf::Keyboard::isKeyPressed(keyBinds[Keybinds::LOOK_DOWN]))
	//			cam->setZHeight(cam->getZHeight() - 0.01f);

	//		if (sf::getLength(velocity) > this->controllableComponent->maxSpeed) {
	//			velocity = sf::getNormalized(velocity) * this->controllableComponent->maxSpeed;
	//		}
	//		//Move
	//		if (sf::Keyboard::isKeyPressed(keyBinds[Keybinds::SPRINT]))
	//			playerTransform->position += velocity * (this->controllableComponent->sprintMultiplier * deltaTime);
	//		else
	//			playerTransform->position += velocity * (this->controllableComponent->movementMultiplier * deltaTime);
	//		colliderComponent->border.top = this->playerTransform->position.y - (colliderComponent->border.height / 2);
	//		colliderComponent->border.left = this->playerTransform->position.x - (colliderComponent->border.width / 2);

	//		if (!cam)
	//			return;
	//		cam->setPosition(playerTransform->position);
	//		cam->setRotation(playerTransform->rotation);
	//	}
	//}
void PlayerController::OnRender(){ }
void PlayerController::OnFixedUpdate(float fixedDeltaTime){}

void PlayerController::OnEventLoop(sf::Event event) {
	sf::Vector2i currentMousePosition = sf::Mouse::getPosition();
	sf::Vector2i deltaMousePosition = currentMousePosition - previousMousePosition;
	float deltaTime = (Config::getConfig()).getDeltaTime();
	previousMousePosition = currentMousePosition;
	std::shared_ptr<Camera> cam = this->camera.lock();
	if (playerTransform != nullptr && playerSprite != nullptr && controllableComponent != nullptr)
	{
		if (this->controllableComponent->enabled)
		{
			sf::Vector2f forward = this->playerTransform->rotation * this->controllableComponent->maxSpeed;
			sf::Vector2f right = this->playerTransform->rotation * this->controllableComponent->maxSpeed;
			right = sf::getRotated(right, -90);
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code== keyBinds[Keybinds::FORWARDS])
					keyStates[Keybinds::FORWARDS]=true;
				else if (event.key.code == keyBinds[Keybinds::BACKWARDS])
					keyStates[Keybinds::BACKWARDS] = true;

				if (event.key.code == keyBinds[Keybinds::RIGHT])
					keyStates[Keybinds::RIGHT] = true;
				else if (event.key.code == keyBinds[Keybinds::LEFT])
					keyStates[Keybinds::LEFT] = true;
			
				if (event.key.code == keyBinds[Keybinds::LOOK_RIGHT])
					keyStates[Keybinds::LOOK_RIGHT] = true;
				else if (event.key.code == keyBinds[Keybinds::LOOK_LEFT])
					keyStates[Keybinds::LOOK_LEFT] = true;
				if (cam != nullptr && event.key.code == Keybinds::LOOK_UP)
					keyStates[Keybinds::LOOK_UP] = true;
				else if (cam != nullptr && event.key.code == Keybinds::LOOK_DOWN)
					keyStates[Keybinds::LOOK_DOWN] = true;
			}else if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == keyBinds[Keybinds::FORWARDS])
					keyStates[Keybinds::FORWARDS] = false;
				else if (event.key.code == keyBinds[Keybinds::BACKWARDS])
					keyStates[Keybinds::BACKWARDS] = false;

				if (event.key.code == keyBinds[Keybinds::RIGHT])
					keyStates[Keybinds::RIGHT] = false;
				else if (event.key.code == keyBinds[Keybinds::LEFT])
					keyStates[Keybinds::LEFT] = false;

				if (event.key.code == keyBinds[Keybinds::LOOK_RIGHT])
					keyStates[Keybinds::LOOK_RIGHT] = false;
				else if (event.key.code == keyBinds[Keybinds::LOOK_LEFT])
					keyStates[Keybinds::LOOK_LEFT] = false;
				if (cam != nullptr && event.key.code == keyBinds[Keybinds::LOOK_UP])
					keyStates[Keybinds::LOOK_UP] = false;
				else if (cam != nullptr && event.key.code == keyBinds[Keybinds::LOOK_DOWN])
					keyStates[Keybinds::LOOK_DOWN] = false;
			}
			//printf("\tVelocity at the End of Event Loop %f,%f\n", velocity.x, velocity.y);
		}
	}
}

void PlayerController::OnDestroy(){}

void PlayerController::setKeyBind(Keybinds key, sf::Keyboard::Key key_code){}
void PlayerController::setSensitivity(float sensitivity){}
void PlayerController::setPlayer(Entity* player, std::shared_ptr<Camera> camera) {
	this->playerTransform = player->getComponent<TransformComponent>();
	this->playerSprite = player->getComponent<SpriteComponent>();
	this->controllableComponent = player->getComponent<ControllableComponent>();
	this->camera = std::weak_ptr<Camera>(camera);
}
void PlayerController::setCamera(std::shared_ptr<Camera> cam) {
	this->camera = std::weak_ptr<Camera>(cam);
}
void PlayerController::setMovementMultiplier(float movementMultiplier) {
	this->controllableComponent->movementMultiplier = movementMultiplier;
}
float PlayerController::getSensitivity() { return this->controllableComponent->sensitivity; };

void PlayerController::renderImGui(){
	if (ImGui::CollapsingHeader("Player Controller Script")) {
		if (ImGui::Button("Unbind Camera")) {
			setCamera(nullptr);
		}
	}
}