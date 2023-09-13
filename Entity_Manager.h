#pragma once
#include "entt-master/single_include/entt/entt.hpp"
class Entity_Manager {

public:
	/**
	* @brief Function to access the singleton instance of the Entity manager
	*/
	static Entity_Manager& getEntityManager();
	entt::registry& getRegistry();
private:
	entt::registry m_registry;
	// Private constructor for singleton instance
	Entity_Manager();
	// Private copy constructor and assignment operator to prevent copy
	Entity_Manager(const Entity_Manager&) = delete;
	static Entity_Manager m_singleton;
	Entity_Manager& operator=(const Entity_Manager&) = delete;
};