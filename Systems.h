#pragma once
#include "System.h"
#include "Components.h"
#include "CoreAdditions.h"
#include "Core.h"
//Entity2D behavior class
class DVDLogoBehaviour :public Actor {
public:
	DVDLogoBehaviour();
	void OnCreate()override;
	void OnUpdate(float deltaTime)override;
	void OnFixedUpdate(float fixedDeltaTime)override;
	void OnRender()override;
	void OnDestroy()override;
	void move(float deltaTime);
	~DVDLogoBehaviour();
	SpriteComponent* spriteComponent;
	sf::Vector2f velocity;
};