#pragma once
#include "entt.hpp"
#include "imgui.h"
#include "imgui-SFML.h"
#include "Core/include/Resource_Manager.h"
#include "Core/include/Entity.h"
#include "Core/include/System.h"
#include "Core/include/Config.h"
#include "Core/include/CoreComponents.h"
#include "Engine/include/PlayerController.h"
/*
 * @brief This template Scene class will provide all the methods that will be called by the Game class
*/
class Scene {
public:
    // Lifecycle methods //
    virtual void onCreate()=0;
    virtual void onUpdate(float deltaTime)=0;
    virtual void onFixedUpdate(float fixedDeltaTime)=0;
    //Should return the canvas result as a sprite and is called every render call
    virtual void onRender()=0;
    virtual void renderImGui();
    virtual void renderEntitiesImGui();
    virtual void onDestroy()=0;
    virtual void refresh() = 0;
    virtual void onEventLoop(sf::Event event) {}
    
    //Scene manipulation functions //
    entt::entity addEntity();
    void removeEntity(entt::entity);
    void createCanvas(std::string name,int width, int height);
    void deleteCanvas(std::string name);
    std::unordered_map<std::string, std::shared_ptr<sf::RenderTexture>>& getCanvasMap();
    std::string& getcurrenCanvas();
    std::vector<std::shared_ptr<Entity>>& getEntityList();

    //Entity manipulation functions/
    template <typename T>
    T* addComponent(entt::entity);
    template <typename T>
    T* addComponent(entt::entity,T component);
    template <typename T>
    void removeComponent(entt::entity);

    template <typename T>
    T* getComponent(entt::entity);
    std::unordered_map<std::string,std::shared_ptr<sf::RenderTexture>> canvasMap;
    std::string currentCanvas;
    sf::Sprite canvasSprite;
    entt::registry registry;
    unsigned int entity_counter;//This will only count upwards
    std::vector<std::shared_ptr<Entity>>entities;
    bool canvas_available=false;
};

//Entity manipulation functions/
template <typename T>
T* Scene::addComponent(entt::entity  entity) {
    int i = 0;
    for (auto ent : this->entities) {
        if (ent->getHandle() == entity)
            break;
        i++;
    }
    if (i == this->entities.size())
        return nullptr;
    return this->entities[i]->addComponent<T>();
}
template <typename T>
T* Scene::addComponent(entt::entity  entity,T component) {
    int i = 0;
    for (auto ent : this->entities) {
        if (ent->getHandle() == entity)
            break;
        i++;
    }
    if (i == this->entities.size())
        return nullptr;
    return this->entities[i]->addComponent<T>(component);
}

template <typename T>
void Scene::removeComponent(entt::entity  entity) {
    int i = 0;
    for (auto ent : this->entities) {
        if (ent->getHandle() == entity)
            break;
        i++;
    }
    if (i == this->entities.size())
        return;
    if (entities[i]->hasComponent<T>())
        this->entities[i]->removeComponent<T>();
}
template <typename T>
T* Scene::getComponent(entt::entity entity) {
    int i = 0;
    for (auto ent : this->entities) {
        if (ent->getHandle() == entity)
            break;
        i++;
    }
    if (i == this->entities.size())
        return nullptr;
    return this->entities[i]->getComponent<T>();
}
