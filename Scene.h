#pragma once
#include "Resource_Manager.h"
#include "entt.hpp"
#include "Entity.h"
#include "System.h"
#include "Config.h"
#include "imgui.h"
#include "imgui-SFML.h"
/*
 * @brief This template Scene class will provide all the methods that will be called by the Game class
*/
class Scene {
public:
    // Lifecycle methods
    virtual void onCreate()=0;
    virtual void onUpdate(float deltaTime)=0;
    virtual void onFixedUpdate(float fixedDeltaTime)=0;
    //Should return the canvas result as a sprite and is called every render call
    virtual sf::Sprite onRender()=0;
    virtual void renderImGui()=0;
    virtual void renderEntitiesImGui()=0;
    virtual void onDestroy()=0;
    virtual void onEventLoop(sf::Event event) {}
protected:
    sf::RenderTexture canvas;
    sf::Sprite canvasSprite;
    entt::registry registry;
    std::vector<std::shared_ptr<Entity>>entities;
};