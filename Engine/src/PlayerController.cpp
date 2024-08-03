#include "Engine\include\PlayerController.h"
PlayerController::PlayerController() {
	OnCreate();
	this->camera = std::weak_ptr<Entity>();
	this->player = std::weak_ptr<Entity>();
}
PlayerController::PlayerController(Entity* player, Entity* camera):PlayerController() {
	OnCreate();
	if(camera!=nullptr)
		this->camera = std::weak_ptr(std::shared_ptr<Entity>(camera));
	if (player != nullptr)
		this->player= std::weak_ptr(std::shared_ptr<Entity>(player));
}
void PlayerController::OnCreate(){
	previousMousePosition = sf::Mouse::getPosition();
}
void PlayerController::OnUpdate(float deltaTime) {
	if (!enabled)return;
	sf::Vector2f velocity = sf::Vector2f(0, 0);
	sf::Vector2i currentMousePosition = sf::Mouse::getPosition();
	sf::Vector2i deltaMousePosition = currentMousePosition - previousMousePosition;
	previousMousePosition = currentMousePosition;
	std::shared_ptr<Entity> cam = this->camera.lock();
	std::shared_ptr<Entity> player = this->player.lock();
	
	ControllableComponent* plyrCtrl = nullptr;
	TransformComponent* plyrTran = nullptr;
	
	CameraComponent* camComp = nullptr;
	TransformComponent* camTran = nullptr;
	
	if (player != nullptr) {
		plyrCtrl = player->getComponent<ControllableComponent>();
		plyrTran = cam->getComponent<TransformComponent>();
	}
	if (cam != nullptr) {
		camComp = cam->getComponent<CameraComponent>();
		camTran = cam->getComponent<TransformComponent>();
	}

	if (plyrTran != nullptr&& plyrCtrl != nullptr)
	{
		if (plyrCtrl->enabled)
		{
			sf::Vector2f forward = plyrTran->rotation * plyrCtrl->maxSpeed;
			sf::Vector2f right = plyrTran->rotation * plyrCtrl->maxSpeed;
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
				velocity *= (plyrCtrl->sprintMultiplier)*4;
			}
			else
				velocity *= (plyrCtrl->movementMultiplier);

			if (keyStates[Keybinds::LOOK_RIGHT])
				sf::rotate(plyrTran->rotation, -plyrCtrl->turnAngle * deltaTime);
			else if (keyStates[Keybinds::LOOK_LEFT])
				sf::rotate(plyrTran->rotation, plyrCtrl->turnAngle * deltaTime);
			if (camComp != nullptr && keyStates[Keybinds::LOOK_UP])
				camComp->zHeight -= 0.01f;
			else if (camComp != nullptr && keyStates[Keybinds::LOOK_DOWN])
				camComp->zHeight += 0.01f;
		}

		if (sf::getLength(velocity) > plyrCtrl->maxSpeed) {
			velocity = sf::getNormalized(velocity) * plyrCtrl->maxSpeed;
		}
		plyrTran->position += velocity * (plyrCtrl->movementMultiplier * deltaTime);
		if (player->hasComponent<ColliderComponent>())
		{
			ColliderComponent* colComp = player->getComponent<ColliderComponent>();
			colComp->border.top = plyrTran->position.y - (colComp->border.height / 2);
			colComp->border.left = plyrTran->position.x - (colComp->border.width / 2);
		}

		if (camTran == nullptr)
			return;
		camTran->position = plyrTran->position;
		camTran->rotation = plyrTran->rotation;
		camComp->setPlaneNormalDirection(camTran->rotation);
	}
}
void PlayerController::OnRender() { }
void PlayerController::OnFixedUpdate(float fixedDeltaTime) {}

void PlayerController::OnEventLoop(sf::Event event) {
	if (!enabled)return;
	std::shared_ptr<Entity> cam = this->camera.lock();
	if (player.lock()!=nullptr)
	{
		ControllableComponent* plyrCtrl = player.lock()->getComponent<ControllableComponent>();
		TransformComponent* plyrTran = player.lock()->getComponent<TransformComponent>();
		if (plyrCtrl->enabled)
		{
			sf::Vector2f forward = plyrTran->rotation * plyrCtrl->maxSpeed;
			sf::Vector2f right = plyrTran->rotation * plyrCtrl->maxSpeed;
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
void PlayerController::setPlayer(Entity* player, std::shared_ptr<Entity> camera) {
	this->player = std::weak_ptr<Entity>(std::shared_ptr<Entity>(player));
	this->camera = std::weak_ptr<Entity>(std::shared_ptr<Entity>(camera));
}
void PlayerController::setCamera(std::shared_ptr<Entity> cam) {
	this->camera = std::weak_ptr<Entity>(cam);
}

void PlayerController::renderImGui(){
	if (ImGui::CollapsingHeader("Player Controller Script")) {
		ImGui::Indent();
		std::string playerName = "";
		if (this->player.lock()) {
			playerName = this->player.lock()->getName();
		}
		else {
			playerName = "None";
		}
		std::string cameraName = "";
		if (this->camera.lock()) {
			cameraName = this->camera.lock()->getName();
		}
		else {
			cameraName = "None";
		}

		ImGui::Text("Player Bound: %s", ((this->player.lock()) ? playerName.c_str() : "None"));
		if (ImGui::BeginDragDropTarget()) {
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("_ENTITY_PTR_")) {
				std::shared_ptr<Entity> player = *static_cast<std::shared_ptr<Entity>*>(payload->Data);
				if (player->hasComponent<TransformComponent>()&& player->hasComponent<ControllableComponent>()) {
					this->player = std::weak_ptr<Entity>(player);
					ImGui::Text("Selected %s as player", player->getName().c_str());
				}
				else printf("Entity doesn't have transform or controllable component\n");
			}
			ImGui::EndDragDropTarget();
		}
		ImGui::Text("Target Camera: %s", ((this->camera.lock())?cameraName.c_str():"None"));
		if (ImGui::BeginDragDropTarget()) {
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("_ENTITY_PTR_")) {
				std::shared_ptr<Entity> cam = *static_cast<std::shared_ptr<Entity>*>(payload->Data);
				if (cam->hasComponent<CameraComponent>()) {
					this->camera = std::weak_ptr<Entity>(cam);
					ImGui::Text("Selected %s as camera",cam->getName().c_str());
				}
				else printf("Entity does not have camera component\n");
			}
			ImGui::EndDragDropTarget();
		}
		ImGui::Checkbox("Enabled##plyrScrpt", &this->enabled);
		ImGui::Unindent();
	}
}