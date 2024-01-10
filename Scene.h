#pragma once
#include "Resource_Manager.h"
#include "Map_Reader.h"
#include "entt.hpp"
#include "System.h"

class Scene {
public:
    Scene();
    // Lifecycle methods
    void onCreate();
    void onDestroy();
    void onStart();
    void onUpdate(float deltaTime);
    void onFixedUpdate(float fixedDeltaTime);
    void onRender(sf::RenderTexture& canvas);
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