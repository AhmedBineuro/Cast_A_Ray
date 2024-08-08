#pragma once
#include "imgui.h"
#include "Engine/include/Systems.h"
#include "Core/include/Scene.h"
//For some reason dividing this file into a h and cpp file causes "unresolved external symbol function" errors

// This is officially the scene for wolfenstien 3D style games!
class DDAScene :public Scene {
public:

	DDAScene() {
		this->map = Map();
		this->canvasSprite = sf::Sprite();
		this->onCreate();
	}
	DDAScene(std::string mapName) {
		this->map = Map(mapName);
		std::shared_ptr<Entity> cam;
		this->canvasSprite = sf::Sprite();
		this->onCreate();
	}
	void onCreate() override{
		currentMap = 0;
		/**
		* Additional Code Here
		*/
		createCanvas("Main", 800, 800);
		this->currentCanvas = "Main";
		entt::entity player = addEntity();
		addComponent(player, TransformComponent());
		addComponent(player, CameraComponent());
		addComponent(player, IntegratedScriptComponent());
		addComponent(player, ControllableComponent());
		addComponent(player, CanvasComponent());
		addComponent(player, ColliderComponent());

		auto trans = getComponent<TransformComponent>(player);
		trans->position = sf::Vector2f(7.3, 2.5);
		auto intScript = getComponent<IntegratedScriptComponent>(player);
		intScript->scripts.push_back(std::make_shared<PlayerController>());
		((PlayerController*)intScript->scripts[0].get())->setPlayer(this->entities[0]);
		((PlayerController*)intScript->scripts[0].get())->setCamera(this->entities[0]);
		((PlayerController*)intScript->scripts[0].get())->enabled = true;
		auto can = getComponent<CanvasComponent>(player);
		can->canvas = this->canvasMap[this->currentCanvas];
		auto camComp = getComponent<CameraComponent>(player);

	}
	void onUpdate(float deltaTime) override{
		Config& config = Config::getConfig();
		this->canvas_available = (this->canvasMap.find(this->currentCanvas) != this->canvasMap.end());
		Systems::EntityScriptSystem::OnUpdate(deltaTime, registry);
		Systems::WolfCollisionSystem(registry, map);
		/**
		* Additional Code Here
		*/
	}
	void onFixedUpdate(float fixedDeltaTime) override{
		Systems::EntityScriptSystem::OnFixedUpdate(fixedDeltaTime, registry);

		/**
		* Additional Code Here
		*/
	}
	void onRender() override{
		for (auto canvas : this->canvasMap)
			canvas.second->clear();

		Systems::DDARenderSystem::renderWalls(registry, map);
		Systems::EntityScriptSystem::OnRender(registry);
		if (this->canvas_available)
		{
			this->canvasMap[this->currentCanvas]->display();
			canvasSprite.setTexture(this->canvasMap[this->currentCanvas]->getTexture());
		}
		for (auto canvas : this->canvasMap)
			canvas.second->display();
		/**
		* Additional Code Here
		*/
	}
	void onDestroy() override{
		/**
		* Additional Code Here
		 */
	}

	void refresh(){
		this->map.refreshMap();
	}


	void onEventLoop(sf::Event event){
		Systems::EntityScriptSystem::OnEventLoop(registry, event);
	}

	~DDAScene() {
		this->onDestroy();
	}
	Map map;
	int currentMap;
};
