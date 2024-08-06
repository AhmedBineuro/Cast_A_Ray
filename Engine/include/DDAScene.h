#pragma once
#include "imgui.h"
#include "Engine/include/Systems.h"
#include "Core/include/Scene.h"
//For some reason dividing this file into a h and cpp file causes "unresolved external symbol function" errors

// This is officially the scene for wolfenstien 3D style games!
class DDAScene :public Scene {
public:
	DDAScene();
	DDAScene(std::string mapName);
	virtual void onCreate() override;
	virtual void onUpdate(float deltaTime) override;
	virtual void onEventLoop(sf::Event event) override;
	virtual void onFixedUpdate(float fixedDeltaTime) override;
	virtual sf::Sprite& onRender() override;
	virtual void onDestroy() override;

	void refresh();

	~DDAScene();
	Map map;
	int currentMap;
};

DDAScene::DDAScene() {
	this->map = Map();
	this->onCreate();
}
DDAScene::DDAScene(std::string mapName) {
	this->map = Map(mapName);
	std::shared_ptr<Entity> cam;
	this->onCreate();
}
void DDAScene::onCreate() {
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

}
void DDAScene::onUpdate(float deltaTime) {
	Config& config = Config::getConfig();
	Systems::EntityScriptSystem::OnUpdate(deltaTime, registry);
	Systems::WolfCollisionSystem(registry, map);
	/**
	* Additional Code Here
	*/
}
void DDAScene::onFixedUpdate(float fixedDeltaTime) {
	Systems::EntityScriptSystem::OnFixedUpdate(fixedDeltaTime, registry);

	/**
	* Additional Code Here
	*/
}
sf::Sprite& DDAScene::onRender() {
	bool canvas_valid = this->canvasMap.find(this->currentCanvas) != this->canvasMap.end();
	if (canvas_valid)
	{
		this->canvasMap[this->currentCanvas]->setActive(true);
	}
	if (canvas_valid)
		this->canvasMap[this->currentCanvas]->clear();
	Systems::DDARenderSystem::renderWalls(registry, map);
	Systems::EntityScriptSystem::OnRender(registry);
	if (canvas_valid)
	{
		this->canvasMap[this->currentCanvas]->draw(canvasSprite);
		this->canvasMap[this->currentCanvas]->display();
		canvasSprite.setTexture(this->canvasMap[this->currentCanvas]->getTexture());
	} 
	/**
	* Additional Code Here
	*/

	return canvasSprite;
}
void DDAScene::onDestroy() {
	/**
	* Additional Code Here
	 */
}

void DDAScene::refresh() {
	this->map.refreshMap();
}


void DDAScene::onEventLoop(sf::Event event) {
	Systems::EntityScriptSystem::OnEventLoop(registry, event);
}

DDAScene::~DDAScene() {
	this->onDestroy();
}