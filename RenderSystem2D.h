#pragma once
#include "System.h"
#include "CoreComponents.h"
#include "Components.h"
#include "Core.h"

class RenderSystem2D :public System {
public:
	RenderSystem2D();
	RenderSystem2D(sf::RenderTexture& renderTarget);
	void update(entt::registry& registry);
	void setTarget(sf::RenderTexture* renderTarget);
private:
	sf::RenderTexture* renderTarget;
};