#pragma once
#include "System.h"
#include "Components.h"
#include "CoreComponents.h"
#include "Core.h"
class ScriptSystem {
public:
	void OnUpdate(float deltaTime, entt::registry& registry);
	void OnFixedUpdate(float fixedDeltaTime, entt::registry& registry);
	void OnRender(entt::registry& registry);
};