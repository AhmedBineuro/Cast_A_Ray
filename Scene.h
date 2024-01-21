#pragma once
#include "Resource_Manager.h"
#include "Map_Reader.h"
#include "entt.hpp"
#include "System.h"

/*
 * @brief This template Scene class will provide all the methods that will be called by the Game class
 * @note When inheriting call the constructor/destructor of this super class to perform the onCreate/onDelete function or call it manually in the constructor/destructor
*/
class Scene {
public:
    Scene() { onCreate(); };
    // Lifecycle methods
    virtual void onCreate()=0;
    virtual void onStart()=0;
    virtual void onUpdate(float deltaTime)=0;
    virtual void onFixedUpdate(float fixedDeltaTime)=0;
    virtual void onRender(sf::RenderTexture& canvas)=0;
    virtual void onDestroy()=0;
    ~Scene() { onDestroy(); }
private:
    template <typename T>
    bool isSystemPresent();
	entt::registry registry;
	std::vector<std::shared_ptr<System>> systems;
};

template <typename T>
bool Scene::isSystemPresent() {
    for (auto& system : systems) {
        if (typeid(T) == typeid(system)) {
            return true;
        }
        return false;
    }
}