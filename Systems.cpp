#include "Systems.h"

/**
* RenderSystem2D Declarations
*/
RenderSystem2D::RenderSystem2D() {
	this->renderTarget = NULL;
}
RenderSystem2D::RenderSystem2D(sf::RenderTarget& renderTarget) {
	this->renderTarget = &renderTarget;
}
void RenderSystem2D::update(entt::registry& registry) {
	if (renderTarget == NULL)
		return;
	renderTarget->clear(sf::Color::White);
	//Get the list of entities with this component
	auto view = registry.view<RenderComponent,SpriteComponent>();
	for (auto entity : view) {
		if (registry.get<RenderComponent>(entity).enabled) {
			SpriteComponent& sprite = registry.get<SpriteComponent>(entity);
			renderTarget->draw(sprite.sprite);
		}
	}
}
///////////////////////////////////////////////////////

/**
* ScriptSystem
*/
void ScriptSystem::OnUpdate(float deltaTime, entt::registry& registry) {
	auto view = registry.view<ScriptComponent>();
	for (auto entity : view) {
		ScriptComponent& script = registry.get<ScriptComponent>(entity);
		script.script->OnUpdate(deltaTime);
	}
}
void ScriptSystem::OnFixedUpdate(float fixedDeltaTime, entt::registry& registry) {
	auto view = registry.view<ScriptComponent>();
	for (auto entity : view) {
		ScriptComponent& script = registry.get<ScriptComponent>(entity);
		script.script->OnFixedUpdate(fixedDeltaTime);
	}
}
void ScriptSystem::OnRender(entt::registry& registry) {
	auto view = registry.view<ScriptComponent>();
	for (auto entity : view) {
		ScriptComponent& script = registry.get<ScriptComponent>(entity);
		script.script->OnRender();
	}
}
///////////////////////////////////////////////////////