#pragma once
#include "Scene.h"
#include "RenderSystem2D.h"
#include "ScriptSystem.h"
#include "Entity2D.h"
#include "Player.h"

//Normal 2D Rendering Scene
class Scene2D :public Scene {
public:
	Scene2D();
	void onCreate();
	void onUpdate(float deltaTime);
	void onFixedUpdate(float fixedDeltaTime);
	//Should return the canvas result as a sprite and is called every render call
	sf::Sprite onRender();
	void onDestroy();
	Entity* createEntity();
	~Scene2D();
protected:
	entt::registry registry;
	std::vector<std::shared_ptr<Entity>>entities;
	RenderSystem2D renderSystem;
	ScriptSystem scriptSystem;
};