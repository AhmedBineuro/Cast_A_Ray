#pragma once
#ifndef DDA_SCENE_H
#define DDA_SCENE_H
#include "Scene2D.h"
#include "Player.h"

// This is officially the scene for wolfenstien 3D style games!
class DDAScene :public Scene2D {
public:

	DDAScene() :Scene2D() {
		this->player = std::make_shared<Player>(&this->registry, sf::Vector2f(2, 2));
		this->entities.push_back(player);
		this->player->camera->linkRenderTarget(&this->canvas);
		this->mapList.resize(0);
		this->onCreate();
	}
	DDAScene(std::vector<std::string>mapNames) :Scene2D() {
		this->mapList.resize(0);
		this->player = std::make_shared<Player>(&this->registry, sf::Vector2f(2, 2));
		this->entities.push_back(player);
		this->player->camera->linkRenderTarget(&this->canvas);
		for (auto& name : mapNames) {
			mapList.push_back(Map(name));
		}
		this->onCreate();
	}
	virtual void onCreate() override{
		/**
		* Additional Code Here
		*/
		if (mapList.size() <= 0)
			return;
		currentMap = 0;
		MapTagComponent tag;
		tag.mapName = mapList[currentMap].getMapName();
		this->player->addComponent(tag);
		this->player->camera->addComponent(tag);
		this->playerTransform = player->getComponent<TransformComponent>();
		this->cameraComponent = this->player->camera->getComponent<CameraComponent>();
		playercontroller = this->player->getComponent<PlayerController>();
	}
	virtual void onUpdate(float deltaTime) override{
		Config& config = Config::getConfig();
		sf::Vector2u window = config.getDimensions();
		if (canvas.getSize() != window) {
			std::cout << "Old Dimensions: " << canvas.getSize().x << " , " << canvas.getSize().y << std::endl;
			std::cout << "New Dimensions: " << window.x << " , " << window.y << std::endl;
			this->canvas.create(window.x, window.y);
		}
		Systems::EntityScriptSystem::OnUpdate(deltaTime, registry);
		Systems::WolfCollisionSystem(registry, mapList);
		/**
		* Additional Code Here
		*/
	}
	virtual void onFixedUpdate(float fixedDeltaTime) override{
		Systems::EntityScriptSystem::OnFixedUpdate(fixedDeltaTime, registry);

		/**
		* Additional Code Here
		*/
	}
	virtual sf::Sprite onRender() override {
		Config& config = Config::getConfig();
		Settings settings = config.getSettings();
		canvas.clear();
		Systems::DDARenderSystem(registry, mapList);
		this->mapList[currentMap].draw(canvas);
		Systems::RenderSystem2D(registry, canvas);
		Systems::EntityScriptSystem::OnRender(registry);
		canvasSprite.setTexture(canvas.getTexture());
		/**
		* Additional Code Here
		*/

		return canvasSprite;
	}
	virtual void onDestroy()override {
		/**
		* Additional Code Here
		 */
	}
	// @ TODO Basically the maps don't bind and I want to switch 
	// from using an unordered map in the system, to using a reference to 
	// the vector of maps
	void changeMap(std::string mapName) {
		int i = 0;
		for (auto& map : this->mapList) {
			if (map.getMapName() == mapName)
				break;
			i++;
		}
		if (i >= this->mapList.size()) {
			return;
		}
		MapTagComponent newTag;
		newTag.mapName = mapName;
		if (this->player->hasComponent< MapTagComponent>())
			this->player->replaceComponent<MapTagComponent>(newTag);
		else this->player->addComponent(newTag);
		if (this->player->camera->hasComponent< MapTagComponent>())
			this->player->camera->replaceComponent<MapTagComponent>(newTag);
		else this->player->camera->addComponent(newTag);
		currentMap = i;
	}
	virtual void renderDebug() override{
		ImGui::Begin("Player settings");
		if (ImGui::BeginTabBar("Player Properties"))
		{
			if (ImGui::BeginTabItem("Transform")) {
				ImGui::Text("Position:");
				ImGui::InputFloat("X:", &this->playerTransform->position.x);
				ImGui::InputFloat("Y:", &this->playerTransform->position.y);

				ImGui::Text("Rotation:");
				ImGui::InputFloat("X:", &this->playerTransform->rotation.x);
				ImGui::InputFloat("Y:", &this->playerTransform->rotation.y);
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("Camera Component")) {
				ImGui::Checkbox("Enabled", &this->cameraComponent->enabled);
				ImGui::Checkbox("Fisheye", &this->cameraComponent->fisheye);
				ImGui::InputFloat("Render Distance", &this->cameraComponent->renderDistance);
				ImGui::EndTabItem();
			}
			ImGui::EndTabBar();
		}
		ImGui::End();
	}

	~DDAScene(void) {
		this->onDestroy();	
	}
protected:
	PlayerController* playercontroller;
	TransformComponent* playerTransform;
	CameraComponent* cameraComponent;
	std::vector<Map> mapList;
	int currentMap;
	std::shared_ptr<Player> player;
};

#endif