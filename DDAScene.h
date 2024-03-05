#pragma once
#ifndef DDA_SCENE_H
#define DDA_SCENE_H
#include "./include/Scene2D.h"
#include "./include/Player.h"

// This is officially the scene for wolfenstien 3D style games!
class DDAScene :public Scene2D {
public:
	DDAScene();
	DDAScene(std::vector<std::string>mapNames);
	virtual void onCreate() override;
	virtual void onUpdate(float deltaTime) override;
	virtual void onFixedUpdate(float fixedDeltaTime) override;
	//Should return the canvas result as a sprite and is called every render call
	virtual sf::Sprite onRender() override;
	virtual void onDestroy() override;
	virtual void renderDebug() override; // ImGui Debug Stuff
	void changeMap(std::string mapName);
	~DDAScene(void) {
		this->onDestroy();	
	}
protected:
	PlayerController* playercontroller;
	TransformComponent* playerTransform;
	std::vector<Map> mapList;
	int currentMap;
	std::shared_ptr<Player> player;
};
#endif