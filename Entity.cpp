#include "Entity.h"
template<typename T, typename... Args>
void Entity::addComponent(Args&&... args) {
    registry->emplace<T>(handle, std::forward<Args>(args)...);
}

template<typename T>
T& Entity::getComponent() {
    return registry->get<T>(handle);
}

template<typename T>
void Entity::removeComponent() {
    registry->remove<T>(handle);
}