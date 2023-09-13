#pragma once
#include "entt.hpp"
#include "Entity_Manager.h"
class Entity {
public:
    /**
    * @brief Constructor to create an entity instance in the entity manager
    * When creating a custom entity, the constuctor should call 
    * the superclass entity constructor for functionality with the 
    * entity manager
    */
    Entity();
    
    /**
    * @brief Function to add a component to the entity
    * The function allows the user to add any component for modular entity
    * design
    */
    template<typename T>
    void addComponent(T component);
    
    /**
    * @brief Function to remove component 
    * @note The function is used like this removeComponent<type>()
    */
    template<typename T>
    void removeComponent();
    
    /**
    * @brief Function to get a pointer component
    * @returns a pointer to the component and nullptr if it doesn't exist
    * @note The function is used like this getComponent<type>()
    */
    template<typename T>
    T* getComponent();
private:
    entt::entity handle;
    entt::registry* registry;
};