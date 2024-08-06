#pragma once
#include "entt.hpp"
#include "Core/include/CoreComponents.h"
#include <set>
/**
* @brief The core entity class that any custom entity will be built on. The class will serve as the interface to the entity component system.
* This allows the developer to simply inherit the super basic functions that add, removes, and retrieve components of an entity.
*/
class Entity {
public:
    /**
    * @brief Constructor to create an entity instance in the entity manager
    * When creating a custom entity, the constuctor should call 
    * the superclass entity constructor for functionality with the 
    * entity manager
    */
    Entity(entt::registry *registry);
    
    /**
    * @brief Function to add a component to the entity
    * The function allows the user to add any component for modular entity
    * design
    */
    template<typename T>
    void addComponent(T component);
    
    /**
    * @brief Function to get a pointer component
    * @returns a pointer to the component and nullptr if it doesn't exist
    * @note The function is used like this getComponent<type>()
    */
    template<typename T>
    T* getComponent();

    template<typename T>
    bool hasComponent();

    template<typename T>
    void replaceComponent(T component);

    template<typename T>
    void removeComponent(T component);

    //Still don't know what to do with this
    void setChild(std::shared_ptr<Entity> entity);
    std::set<Component*>* getComponentList();

    
    entt::entity getHandle();
    std::string getName();
    
    void setName(std::string);
    
    virtual ~Entity() {
        this->registry->destroy(this->handle);
    }
    std::string buffer;
protected:
    std::string name;
    entt::entity handle;
    entt::registry* registry;
    std::weak_ptr<Entity> child; // Weak pointer to handle random deletes and stuff
    std::set<Component*> components;
};
template <typename T>
void Entity::addComponent(T component) {
    components.insert(&(registry->emplace<T>(handle, component)));
}

template <typename T>
T* Entity::getComponent() {
    return registry->try_get<T>(handle);
}

template <typename T>
bool Entity::hasComponent() {
    return registry->any_of<T>(handle);
}

template <typename T>
void Entity::replaceComponent(T component) {
    this->components.erase(getComponent<T>());
    this->components.insert(registry->replace<T>(handle, component));
    return;
}
template <typename T>
void Entity::removeComponent(T component) {
    if (hasComponent<T>()) {
        this->components.erase(getComponent<T>());
        registry->remove<T>(handle);
    }
}