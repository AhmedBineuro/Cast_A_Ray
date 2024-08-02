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
		this->onCreate();
	}
	DDAScene(std::string mapName) :Scene() {
		this->map = Map(mapName);
		std::shared_ptr<Entity> cam;
		this->onCreate();
	}
	virtual void onCreate() override{
		currentMap = 0;

		/**
		* Additional Code Here
		*/
	}
	virtual void onUpdate(float deltaTime) override{
		Config& config = Config::getConfig();
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
		bool canvas_valid = this->canvasMap.find(this->currentCanvas) != this->canvasMap.end();
		if(canvas_valid)
			this->canvasMap[this->currentCanvas]->clear();
		Systems::DDARenderSystem::renderWalls(registry, map);
		if (canvas_valid)
			Systems::RenderSystem2D(registry, *this->canvasMap[this->currentCanvas]);
		Systems::EntityScriptSystem::OnRender(registry);
		if (canvas_valid)
			canvasSprite.setTexture(this->canvasMap[this->currentCanvas]->getTexture());
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