#pragma once
#include "entt.hpp"
#include "CoreComponents.h"
class System {
public:
	virtual void update(entt::registry& registry)=0;
	virtual ~System() {};
};