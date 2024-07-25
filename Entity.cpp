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
    if(ImGui::Button("Add Component##addComponent")){
        ImGui::OpenPopup("Component_List");
    }
    //Menu to add the components on the fly
    if(ImGui::BeginPopup("Component_List")){
        if (ImGui::MenuItem("Transform Component")) {
            this->addComponent(TransformComponent());
        }
        //if (ImGui::MenuItem("Script Component")) {
        //    this->addComponent(ScriptComponent());
        //}
        if (ImGui::MenuItem("Render Component")) {
            this->addComponent(RenderComponent());
        }
        if (ImGui::MenuItem("Sprite Component")) {
            this->addComponent(SpriteComponent());
        }
        if (ImGui::MenuItem("Controllable Component")) {
            this->addComponent(ControllableComponent());
        }
        if (ImGui::MenuItem("Camera Component")) {
            this->addComponent(CameraComponent());
        }
        if (ImGui::MenuItem("Map Tag Component")) {
            this->addComponent(MapTagComponent());
        }
        if (ImGui::MenuItem("Collider Component")) {
            this->addComponent(ColliderComponent());
        }
        ImGui::EndPopup();
    }

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

void Entity::setChild(std::shared_ptr<Entity> entity) {
    this->child = std::weak_ptr(entity);
}