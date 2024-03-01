#include "MapColliderSystem.h"


MapColliderSystem::MapColliderSystem() {
	this->mapList = nullptr;
}
MapColliderSystem::MapColliderSystem(Map& map) {
	this->mapList = nullptr;
}
void MapColliderSystem::update(entt::registry& registry) {
	if (this->mapList== nullptr)
		return;
	auto view = registry.view<ColliderComponent, TransformComponent,MapTagComponent>();
	for (auto entity : view) {
		//Check Collision against map tiles using aabb
		ColliderComponent collider = registry.get<ColliderComponent>(entity);
		TransformComponent transform = registry.get<TransformComponent>(entity);
		MapTagComponent mapTag = registry.get<MapTagComponent>(entity);
		sf::Vector2f size = collider.border.getSize();
		collider.border.left = transform.position.x - (size.x / 2);
		collider.border.top = transform.position.y - (size.y / 2);
		float X[2] = { collider.border.left ,collider.border.left + size.x };
		float Y[2] = { collider.border.top,collider.border.top + size.y };
		//Find map index
		int index = 0;
		for (auto& map : *this->mapList) {
			if (map.getMapName() == mapTag.mapName)
				break;
			index++;
		}
		if (index >= this->mapList->size()) {
			continue;
		}
		//Check left right borders
		int i = 0;
		for (auto x : X)
		{
			//If it return the end of the array then it is a solid block
			auto isSolid = std::find((this->mapList[index])->ignoreCollision.begin(), (this->mapList[index])->ignoreCollision.end(), (this->mapList[index])->walls[(int)Y[0]][(int)x]);
			if (isSolid == this->mapList->at(index)->ignoreCollision.end())
			{
				float xOffset = (floor(x) + (1-i)) - x;
				transform.position.x += xOffset;
				collider.border.left += xOffset;
			}
			i++;
		}
		//Check up down borders
		i = 0;
		for (auto y : Y)
		{
			//If it return the end of the array then it is a solid block
			auto isSolid = std::find(linked_map->ignoreCollision.begin(), linked_map->ignoreCollision.end(), linked_map->walls[y][(int)X[0]]);
			if (isSolid == linked_map->ignoreCollision.end())
			{
				float yOffset = (floor(y) + (1 - i)) - y;
				transform.position.y += yOffset;
				collider.border.top += yOffset;
			}
			i++;
		}
	}
}
MapColliderSystem::~MapColliderSystem() {

}
void MapColliderSystem::setMapList(std::vector<Map>& mapList);
	this->mapList = &(mapList);
}