#include "CameraRenderSystem.h"
void CameraRenderSystem::update(entt::registry& registry) {
	if (this->mapList.size() <= 0)
		return;
	Config& config = Config::getConfig();
	Resource_Manager& rm = Resource_Manager::getResourceManager();
	sf::RectangleShape textureSlice(sf::Vector2f(1, 10));
	auto view = registry.view<CameraComponent, MapTagComponent, TransformComponent>();
	for (auto entity : view) {
		CameraComponent& cameracomponent = registry.get<CameraComponent>(entity);
		if (!cameracomponent.enabled)
			continue;
		MapTagComponent& mapTagComponent = registry.get<MapTagComponent>(entity);
		TransformComponent& transformComponent = registry.get<TransformComponent>(entity);
		int index = 0;
		for (auto& map : this->mapList) {
			if (map.getMapName() == mapTagComponent.mapName)
				break;
			index++;
		}
		if (index >= this->mapList.size()) {
			return;
		}
		//If outside the realbounds position wise then just exit
		if (this->mapList[index].walls.size() <= floor(transformComponent.position.y))
			continue;
		else if (this->mapList[index].walls[floor(transformComponent.position.y)].size() <= transformComponent.position.x)
			continue;
			sf::Vector2u windowSize= cameracomponent.target->getSize();
		for (int x = 0; x < windowSize.x; x++) {
			//cameraX is the x-coordinate in the screen space/ camera space
			double cameraX = 2 * x / ((double)windowSize.x) - sf::getLength(cameracomponent.plane) / 2;
			
			sf::Vector2f currentRay = transformComponent.rotation + cameracomponent.plane * (float)cameraX;
			RaycastUtils::RayCollisionInfo collision;
			collision=RaycastUtils::castRay(transformComponent.position,sf::getNormalized(currentRay),mapList[index],cameracomponent.renderDistance);
			
			if (collision.noHit)
				continue;
			//Draw the lines
			int lineHeight = ((windowSize.y * 2.5) / collision.perpindcularDistance);
			int drawStart = (-lineHeight + ((int)windowSize.y)) / 2;
			int drawEnd = (lineHeight + ((int)windowSize.y)) / 2;
			int size = drawEnd - drawStart;
			textureSlice.setSize(sf::Vector2f(1, size));
			textureSlice.setPosition(x, drawStart);
			std::string textureName = this->mapList[index].wallMapping[collision.tag];
			textureSlice.setTexture(&rm.getTexture(textureName));
			sf::Vector2u textSize = textureSlice.getTexture()->getSize();
			int texX = textSize.x * collision.u;
			if ((collision.side == 0 && currentRay.x > 0) || (collision.side == 1 && currentRay.y < 0))
				texX = textSize.x - texX - 1;
			textureSlice.setTextureRect(sf::Rect(texX, 0, 1, (int)textSize.y));
			textureSlice.setSize(sf::Vector2f(textureSlice.getSize().x, lineHeight));
			cameracomponent.target->draw(textureSlice);
		}
		cameracomponent.target->display();
	}
}
void CameraRenderSystem::setMapList(std::vector<Map> &mapList) {
	this->mapList=mapList;
}