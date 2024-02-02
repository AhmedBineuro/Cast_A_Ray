#include "ScriptSystem.h"
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