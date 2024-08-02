#pragma once
#ifndef DDA_SCENE_H
#define DDA_SCENE_H
#include "imgui.h"
#include "Engine/include/Systems.h"
#include "Core/include/imgui_car.h"

// This is officially the scene for wolfenstien 3D style games!
class DDAScene :public Scene {
public:

	DDAScene() :Scene() {
		this->map = Map();
		this->canvas = std::make_shared<sf::RenderTexture>();
		this->onCreate();
	}
	DDAScene(std::string mapName) :Scene() {
		this->map = Map(mapName);
		std::shared_ptr<Entity> cam;
		this->canvas = std::make_shared<sf::RenderTexture>();
		this->onCreate();
	}
	virtual void onCreate() override{
		Config& config = Config::getConfig();
		Settings s = config.getSettings();
		this->canvas->create(s.renderResolution.x, s.renderResolution.y);
		currentMap = 0;
		canvas_map["Main"] = this->canvas;
		canvas_map["Wat"] = nullptr;

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

	//virtual void renderImGui() override{
	//	ImGui::Begin("Scene Information##window");

	//	if (ImGui::BeginTabBar("Scene Information")) {
	//		if (ImGui::BeginTabItem("Scene Properites")) {
	//			ImGui::Text("Current Map: %s", map.getMapName().c_str());
	//			ImGui::Separator();
	//			if (ImGui::Button("Refresh Scene")) {
	//				refresh();
	//			}
	//			ImGui::SameLine();
	//			if (ImGui::Button("Select New Map")) {
	//			
	//			}
	//			ImGui::Separator();

	//			ImGui::EndTabItem();
	//		}
	//		renderEntitiesImGui();
	//		ImGui::EndTabBar();
	//	}
	//	ImGui::End();
	//}

	void onEventLoop(sf::Event event) override{
		Systems::EntityScriptSystem::OnEventLoop(registry,event);
	}

	~DDAScene(void) {
		this->onDestroy();	
	}
protected:
	sf::RenderTexture playerScreen;
	Map map;
	int currentMap;
};

#endif