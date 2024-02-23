#pragma once
#include "System.h"
#include "CoreComponents.h"
#include "RaycastUtils.h"
#include "Config.h"

class CameraRenderSystem : public System {
public:
	void update(entt::registry& registry);
	void setMapList(std::vector<Map>& mapList);
	~CameraRenderSystem() {};
private:
	std::vector<Map> mapList;
};