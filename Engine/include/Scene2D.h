#pragma once
#ifndef SCENE2D_H
#define SCENE2D_H
#include "Core\include\Scene.h"
#include "Systems.h"

//Normal 2D Rendering Scene
class Scene2D :public Scene {
public:
	Scene2D();
	virtual void onCreate() override;
	virtual void onUpdate(float deltaTime) override;
	virtual void onFixedUpdate(float fixedDeltaTime) override;
	virtual //Should return the canvas result as a sprite and is called every render cal overridel
	virtual sf::Sprite& onRender() override;
	virtual void onDestroy() override;
	Entity* createEntity();
	~Scene2D();
protected:
	entt::registry registry;
	std::vector<std::shared_ptr<Entity>>entities;
};
#endif