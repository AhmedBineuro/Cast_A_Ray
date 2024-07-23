#include "Entity.h"
Entity::Entity(entt::registry* registry) {
    this->registry = registry;
    handle = registry->create();
    name = "Entity " + std::to_string((unsigned int)handle);
    buffer = name;
}

entt::entity Entity::getHandle() {
    return this->handle;
}
void Entity::drawImGui() {
    ImGui::Text("Name:");
    ImGui::SameLine();
    ImGui::InputText("##input", buffer.begin()._Unwrapped(), buffer.size());
    ImGui::SameLine();
    if (ImGui::Button("apply##name")) {
        this->name = buffer;
    }
    for (auto component : components) {
        component->draw();
    }
}

std::string Entity::getName() {
    return name;
}
void Entity::setName(std::string name) {
    this->name = name;
    buffer = name;
}

void Entity::setChild(Entity* entity) {
    this->child = entity;
}