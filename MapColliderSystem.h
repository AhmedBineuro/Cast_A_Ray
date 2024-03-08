#pragma once
#include "CoreComponents.h"
#include "Map"
#include "System.h"

class MapColliderSystem: public System{
public:
	MapColliderSystem();
	MapColliderSystem(std::vector<Map>& mapList);
	void update(entt::registry& registry);
	~MapColliderSystem();
	void setMapList(std::vector<Map>& mapList);
private:
	std::vector<Map>* mapList;
};