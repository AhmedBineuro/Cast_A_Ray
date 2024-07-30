#include "Core\include\Entity.h"
Entity::Entity(entt::registry* registry) {
    this->registry = registry;
    handle = registry->create();
    name = "Entity " + std::to_string((unsigned int)handle);
    buffer = name;
    buffer.resize(20);
}

entt::entity Entity::getHandle() {
    return this->handle;
}
std::string Entity::getName() {
    return name;
}
void Entity::setName(std::string name) {
    this->name = name;
    buffer = name;
}

void Entity::setChild(std::shared_ptr<Entity> entity) {
    this->child = std::weak_ptr(entity);
}

std::set<Component*>* Entity::getComponentList()
{
    return &components;
}
