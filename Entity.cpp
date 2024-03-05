#include "Entity.h"
Entity::Entity(entt::registry* registry) {
    this->registry = registry;
    handle = registry->create();
}