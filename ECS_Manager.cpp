#include "ECS_Manager.h"
ECS_Manager ECS_Manager::m_singleton;
entt::registry ECS_Manager::m_registry;
ECS_Manager::ECS_Manager(){}
ECS_Manager &ECS_Manager::getECSManager() {
	static ECS_Manager m_singleton;
	return m_singleton;
}
entt::registry& ECS_Manager::getRegistry() {
	static entt::registry m_registry;
	return m_registry;
}
