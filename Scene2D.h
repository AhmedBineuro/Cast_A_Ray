#pragma once
#include "Scene.h"
#include "RenderSystem2D.h"
#include "ScriptSystem.h"
#include "Entity2D.h"

//Normal 2D Rendering Scene
class Scene2D :public Scene {
public:
	Scene2D();
	virtual void onCreate();
	virtual void onUpdate(float deltaTime);
	virtual void onFixedUpdate(float fixedDeltaTime);
	//Should return the canvas result as a sprite and is called every render call
	virtual sf::Sprite onRender();
	virtual void onDestroy();
	virtual void renderDebug(); // ImGui Debug Stuff
	Entity* createEntity();
	virtual ~Scene2D();
protected:
	entt::registry registry;
	std::vector<std::shared_ptr<Entity>>entities;
	RenderSystem2D renderSystem;
	ScriptSystem scriptSystem;
};