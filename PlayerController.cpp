#include "PlayerController.h"
PlayerController::PlayerController() {
	OnCreate();
	this->playerTransform = nullptr;
	this->playerSprite = nullptr;
	this->controllableComponent = nullptr;
	this->colliderComponent = nullptr;
	this->camera = std::weak_ptr<Entity>();
}
PlayerController::PlayerController(Entity* player, Entity* camera) {
	OnCreate();
	this->playerTransform = player->getComponent<TransformComponent>();
	this->controllableComponent = player->getComponent<ControllableComponent>();
	this->colliderComponent = player->getComponent<ColliderComponent>();
	this->camera = std::weak_ptr(std::shared_ptr<Entity>(camera));
}
void PlayerController::OnCreate(){
	previousMousePosition = sf::Mouse::getPosition();
}
void PlayerController::OnUpdate(float deltaTime) {
	sf::Vector2f velocity = sf::Vector2f(0, 0);
	sf::Vector2i currentMousePosition = sf::Mouse::getPosition();
	sf::Vector2i deltaMousePosition = currentMousePosition - previousMousePosition;
	previousMousePosition = currentMousePosition;
	std::shared_ptr<Entity> cam = this->camera.lock();
	CameraComponent* camComp = nullptr;
	TransformComponent* camTran = nullptr;
	if (cam != nullptr) {
		camComp = cam->getComponent<CameraComponent>();
		camTran = cam->getComponent<TransformComponent>();
	}
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

			// TODO: fix running not working
			if (keyStates[Keybinds::SPRINT])
			{
				velocity *= (this->controllableComponent->sprintMultiplier)*4;
			}
			else
				velocity *= (this->controllableComponent->movementMultiplier);

			if (keyStates[Keybinds::LOOK_RIGHT])
				sf::rotate(this->playerTransform->rotation, -this->controllableComponent->turnAngle * deltaTime);
			else if (keyStates[Keybinds::LOOK_LEFT])
				sf::rotate(this->playerTransform->rotation, this->controllableComponent->turnAngle * deltaTime);
			if (camComp != nullptr && keyStates[Keybinds::LOOK_UP])
				camComp->zHeight -= 0.01f;
			else if (camComp != nullptr && keyStates[Keybinds::LOOK_DOWN])
				camComp->zHeight += 0.01f;
		}

		if (sf::getLength(velocity) > this->controllableComponent->maxSpeed) {
			velocity = sf::getNormalized(velocity) * this->controllableComponent->maxSpeed;
		}
		playerTransform->position += velocity * (this->controllableComponent->movementMultiplier * deltaTime);
		colliderComponent->border.top = this->playerTransform->position.y - (colliderComponent->border.height / 2);
		colliderComponent->border.left = this->playerTransform->position.x - (colliderComponent->border.width / 2);

		if (camTran == nullptr)
			return;
		camTran->position = playerTransform->position;
		camTran->rotation = playerTransform->rotation;
		camComp->setPlaneNormalDirection(camTran->rotation);
	}
}
void PlayerController::OnRender() { }
void PlayerController::OnFixedUpdate(float fixedDeltaTime) {}

void PlayerController::OnEventLoop(sf::Event event) {
	std::shared_ptr<Entity> cam = this->camera.lock();
	if (playerTransform != nullptr && playerSprite != nullptr && controllableComponent != nullptr)
	{
		if (this->controllableComponent->enabled)
		{
			sf::Vector2f forward = this->playerTransform->rotation * this->controllableComponent->maxSpeed;
			sf::Vector2f right = this->playerTransform->rotation * this->controllableComponent->maxSpeed;
			right = sf::getRotated(right, -90);
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == keyBinds[Keybinds::FORWARDS])
					keyStates[Keybinds::FORWARDS] = true;
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
				if (event.key.code == keyBinds[Keybinds::LOOK_UP])
				{
					keyStates[Keybinds::LOOK_UP] = true;
				}
				else if (event.key.code == keyBinds[Keybinds::LOOK_DOWN])
				{
					keyStates[Keybinds::LOOK_DOWN] = true;
				}
				if (event.key.code == keyBinds[Keybinds::SPRINT]){
					keyStates[Keybinds::SPRINT] = true;
				}
			}
			else if (event.type == sf::Event::KeyReleased)
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
				else if (event.key.code == keyBinds[Keybinds::SPRINT])
					keyStates[Keybinds::SPRINT] = false;
			}
		}
	}
}

void PlayerController::OnDestroy(){}

void PlayerController::setKeyBind(Keybinds key, sf::Keyboard::Key key_code){}
void PlayerController::setSensitivity(float sensitivity){}
void PlayerController::setPlayer(Entity* player, std::shared_ptr<Entity> camera) {
	this->playerTransform = player->getComponent<TransformComponent>();
	this->playerSprite = player->getComponent<SpriteComponent>();
	this->controllableComponent = player->getComponent<ControllableComponent>();
	this->camera = std::weak_ptr<Entity>(camera);
}
void PlayerController::setCamera(std::shared_ptr<Entity> cam) {
	this->camera = std::weak_ptr<Entity>(cam);
}
void PlayerController::setMovementMultiplier(float movementMultiplier) {
	this->controllableComponent->movementMultiplier = movementMultiplier;
}
float PlayerController::getSensitivity() { return this->controllableComponent->sensitivity; };

void PlayerController::renderImGui(){
	if (ImGui::CollapsingHeader("Player Controller Script")) {
		std::string cameraName = "";
		if (this->camera.lock()) {
			cameraName = this->camera.lock()->getName();
		}
		else {
			cameraName = "None";
		}
		ImGui::Text("Target Camera: %s", cameraName.c_str());
		if (ImGui::BeginDragDropTarget()) {
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("_ENTITY_PTR_")) {
				std::shared_ptr<Entity> cam = *static_cast<std::shared_ptr<Entity>*>(payload->Data);
				if (cam->hasComponent<CameraComponent>()) {
					this->camera = std::weak_ptr<Entity>(cam);
					ImGui::Text("Selected %s as camera",cam->getName().c_str());
				}
				else printf("Entity is not a Camera Entity\n");
			}
			ImGui::EndDragDropTarget();
		}
		if (ImGui::Button("Unbind Camera")) {
			setCamera(nullptr);
		}
	}
}