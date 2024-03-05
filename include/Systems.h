#pragma once
#include "System.h"
#include "Components.h"
#include "Config.h"
#include "Core.h"
#include "RaycastUtils.h"


namespace Systems {

	void WolfCollisionSystem(entt::registry& registry, std::vector<Map>& mapList);
	void DDARenderSystem(entt::registry& registry, std::vector<Map>&mapList);
	void RenderSystem2D(entt::registry& registry, sf::RenderTexture& renderTarget);
	namespace EntityScriptSystem {
		void OnUpdate(float deltaTime, entt::registry& registry);
		void OnFixedUpdate(float fixedDeltaTime, entt::registry& registry);
		void OnRender(entt::registry& registry);
	};
};