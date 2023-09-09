#pragma once
#include "Components.h"
#include "Core.h"
#include "Resource_Manager.h"
#include <queue>
#include <functional>
struct System {
	int priority;
	std::function<void()> function;
	bool operator<(const System& rhs) const{
		return priority < rhs.priority;
	}
	bool operator>(const System& rhs) const {
		return priority > rhs.priority;
	}
};
class ECS_Manager {

public:
	/**
	* @brief Function to access the singleton instance of the ECS manager
	*/
	static ECS_Manager& getECSManager();

	/**
	* @brief Function to access the singleton instance of the ECS manager
	*/
	entt::registry& getRegistry();

	/**
	* @brief Function to add a system
	*/

private:
	static ECS_Manager m_singleton;
	// Private constructor for singleton instance
	ECS_Manager();
	// Private copy constructor and assignment operator to prevent copy
	ECS_Manager(const ECS_Manager&) = delete;
	// Private registry
	static entt::registry m_registry;
	ECS_Manager operator=(const ECS_Manager&) = delete;
};