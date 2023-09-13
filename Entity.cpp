#include "Entity.h"
Entity::Entity() {
	Entity_Manager &em = Entity_Manager::getEntityManager();
	registry=em.getRegistry();
	handle = registry.create();
}
template <typename T>
void Entity::addComponent(T component) {
	registry.emplace(handle, component);
}

template <typename T>
void Entity::removeComponent() {
	registry.remove_if_exists<T>(handle);
}

template <typename T>
inline T* Entity::getComponent() {
	return registry.try_get<T>(handle);
}