#pragma once
#ifndef DDA_SCENE_H
#define DDA_SCENE_H
#include "Scene2D.h"
#include "Player.h"
#include "imgui.h"

// This is officially the scene for wolfenstien 3D style games!
class DDAScene :public Scene {
public:

	DDAScene() :Scene() {
		this->player = std::make_shared<Player>(&this->registry, sf::Vector2f(2, 2));
		std::shared_ptr<Camera> cam;
		cam = std::make_shared<Camera>(&this->registry, sf::Vector2f(2, 2));
		this->entities.push_back(player);
		this->entities.push_back(cam);
		player->setCamera(cam);
		this->player->setName("Player");
		this->player->camera.lock()->setName("Player Camera");
		this->player->camera.lock()->linkRenderTarget(&(*this->canvas));
		this->map = Map();
		this->canvas = std::make_shared<sf::RenderTexture>();
		this->onCreate();
	}
	DDAScene(std::string mapName) :Scene() {
		this->map = Map(mapName);
		std::shared_ptr<Camera> cam;
		cam = std::make_shared<Camera>(&this->registry, sf::Vector2f(2, 2));
		this->player = std::make_shared<Player>(&this->registry, sf::Vector2f(2, 2));
		this->entities.push_back(player);
		this->entities.push_back(cam);
		player->setCamera(cam);
		
		this->player->camera.lock()->linkRenderTarget(&(*this->canvas));
		this->player->setName("Player");
		this->player->camera.lock()->setName("Player Camera");
		this->canvas = std::make_shared<sf::RenderTexture>();
		this->onCreate();
	}
	virtual void onCreate() override{
		Config& config = Config::getConfig();
		Settings s = config.getSettings();
		this->canvas->create(s.renderResolution.x, s.renderResolution.y);
		currentMap = 0;
		this->playerTransform = player->getComponent<TransformComponent>();
		this->cameraComponent = this->player->camera.lock()->getComponent<CameraComponent>();
		playercontroller = this->player->getComponent<PlayerController>();

		/**
		* Additional Code Here
		*/
	}
	virtual void onUpdate(float deltaTime) override{
		Config& config = Config::getConfig();
		sf::Vector2u canvSize = config.getRenderResolution();
		if (canvas->getSize() != canvSize) {
			this->canvas->create(canvSize.x, canvSize.y);
		}
		Systems::EntityScriptSystem::OnUpdate(deltaTime, registry);
		Systems::WolfCollisionSystem(registry, map);
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
		canvas->clear();
		Systems::DDARenderSystem::renderWalls(registry, map);
		Systems::RenderSystem2D(registry, *canvas);
		Systems::EntityScriptSystem::OnRender(registry);
		canvasSprite.setTexture(canvas->getTexture());
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

	void refresh() override {
		this->map.refreshMap();
	}

	void renderImGui() override{
		ImGui::Begin("Scene Information##window");

		if (ImGui::BeginTabBar("Scene Information")) {
			if (ImGui::BeginTabItem("Scene Properites")) {
				ImGui::Text("Current Map: %s", map.getMapName().c_str());
				ImGui::Separator();
				if (ImGui::Button("Refresh Scene")) {
					refresh();
				}
				ImGui::SameLine();
				if (ImGui::Button("Select New Map")) {
				
				}
				ImGui::Separator();

				ImGui::EndTabItem();
			}
			renderEntitiesImGui();
			ImGui::EndTabBar();
		}
		ImGui::End();
	}

	void onEventLoop(sf::Event event) override{
		Systems::EntityScriptSystem::OnEventLoop(registry,event);
	}

	~DDAScene(void) {
		this->onDestroy();	
	}
protected:
	PlayerController* playercontroller;
	TransformComponent* playerTransform;
	CameraComponent* cameraComponent;
	sf::RenderTexture playerScreen;
	Map map;
	int currentMap;
	std::shared_ptr<Player> player;
};

#endif