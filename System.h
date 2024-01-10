#pragma once
#include "entt.hpp"
class System {
public:
	virtual void update(entt::registry& registry, float deltaTime)=0;
	virtual ~System() {};
};