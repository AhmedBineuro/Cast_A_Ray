#pragma once
#include "Entity.h"
#pragma once
#include "entt.hpp"
class Entity_Factory {

public:
	/**
	* @brief Function to access the singleton instance of the Entity manager
	*/
	static Entity_Factory& getEntityFactory();
	void registerEntity(std::string entityName,)
private:
	static Entity_Factory m_singleton;
	// Private constructor for singleton instance
	Entity_Factory();
	// Private copy constructor and assignment operator to prevent copy
	Entity_Factory(const Entity_Factory&) = delete;
	Entity_Factory& operator=(const Entity_Factory&) = delete;
};