#pragma once
#include "entt.hpp"
class System {
public:
	virtual void update(entt::registry& registry)=0;
	virtual ~System() {};
};