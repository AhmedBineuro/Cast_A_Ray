#include "Entity_Manager.h"
Entity_Manager Entity_Manager::m_singleton;
Entity_Manager::Entity_Manager(){}
Entity_Manager& Entity_Manager::getEntityManager() {
	return m_singleton;
}
entt::registry* Entity_Manager::getRegistry() {
	return &(m_singleton.m_registry);
}