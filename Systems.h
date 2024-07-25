#pragma once
#include "System.h"
#include "Components.h"
#include "Config.h"
#include "Core.h"
#include "RaycastUtils.h"


namespace Systems {
	void WolfCollisionSystem(entt::registry& registry, Map & currentMap);
	namespace DDARenderSystem {
		void renderWalls(entt::registry& registry, Map& currentMap);
		void renderFloors(entt::registry& registry, Map& currentMap);
	}
	void RenderSystem2D(entt::registry& registry, sf::RenderTexture& renderTarget);
	namespace EntityScriptSystem {
		void OnUpdate(float deltaTime, entt::registry& registry);
		void OnFixedUpdate(float fixedDeltaTime, entt::registry& registry);
		void OnRender(entt::registry& registry);
		void OnEventLoop(entt::registry& registry, sf::Event event);
	};
};

namespace Graphics_Helper {
	static std::unordered_map<std::string, sf::Texture*> TextureCache;
	static std::unordered_map<std::string, sf::Image> ImageCache;
	
	//Returns true if found in cache
	bool checkImage(std::string name);

	//Returns true if found in cache
	bool checkTexture(std::string name);

	void addTexture(std::string name);
	void addImage(std::string name);
};