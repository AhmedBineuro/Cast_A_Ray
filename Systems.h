#include "System.h"
#include "Components.h"
#include "Core.h"

class RenderSystem2D :public System {
public:
	RenderSystem2D();
	RenderSystem2D(sf::RenderTarget& renderTarget);
	void update(entt::registry& registry);
private:
	sf::RenderTarget* renderTarget;
};

class ScriptSystem{
public:
	void OnUpdate(float deltaTime,entt::registry& registry);
	void OnFixedUpdate(float fixedDeltaTime, entt::registry& registry);
	void OnRender(entt::registry& registry);
};