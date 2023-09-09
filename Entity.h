#pragma once
#include "entt-master/single_include/entt/entt.hpp"
class Entity {
public:
    // Constructors, destructors, etc.

    template<typename T, typename... Args>
    void addComponent(Args&&... args);

    template<typename T>
    T& getComponent();

    template<typename T>
    void removeComponent();
private:
    entt::entity handle;
    entt::registry* registry;
};