#include "Entity.h"
Entity::Entity(entt::registry* registry) {
    this->registry = registry;
    handle = registry->create();
}

entt::entity Entity::getHandle() {
    return this->handle;
}