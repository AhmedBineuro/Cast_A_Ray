#include "Systems.h"

namespace Systems {

	void WolfCollisionSystem(entt::registry& registry, std::vector<Map>& mapList) {
	auto view = registry.view<ColliderComponent, TransformComponent,MapTagComponent>();
	//
	for (auto entity : view) {
		//Check Collision against map tiles using aabb
		ColliderComponent& collider = registry.get<ColliderComponent>(entity);
		TransformComponent& transform = registry.get<TransformComponent>(entity);
		MapTagComponent& mapTag = registry.get<MapTagComponent>(entity);
		//Find map index
		int index = 0;
		for (auto& map : mapList) {
			if (map.getMapName() == mapTag.mapName)
				break;
			index++;
		}
		if (index >= mapList.size()) {
			continue;
		}
		sf::Vector2f size = collider.border.getSize();
		//Check the borders
		float LeftRight[2] = { collider.border.left, collider.border.left+size.x };
		float UpDown[2] = { collider.border.top, collider.border.top + size.y };
		for (int x = 0; x < 2;x++) {
			for (int y = 0; y < 2; y++) {
				//If the tile is not in the ignore list then resolve collision
				auto iterator=std::find(mapList[index].ignoreCollision.begin(), mapList[index].ignoreCollision.end(), mapList[index].walls[floor(UpDown[y])][floor(LeftRight[x])]);
				if (iterator == mapList[index].ignoreCollision.end())
				{
					std::cout << "Collision!" << std::endl;
					//If the tile x index is 0 (entity's left edge) it means compare against the tile's right edge
					float tileX = floor(LeftRight[x]) + (1*x);
					//If the tile y location is less that means that we have to compare to the bottom edge of the tile
					float tileY = floor(LeftRight[y]) + (1 * y);
					sf::Vector2f offSet=sf::Vector2f(tileX-LeftRight[x], tileY - LeftRight[y]);
					transform.position += offSet;
				}

			}
		}
		
	}
	}
	void DDARenderSystem(entt::registry& registry, std::vector<Map>& mapList) {
		if (mapList.size() <= 0)
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
			//Find map index
			int index = 0;
			for (auto& map : mapList) {
				if (map.getMapName() == mapTagComponent.mapName)
					break;
				index++;
			}
			if (index >= mapList.size()) {
				continue;
			}
			//If outside the real bounds position wise then just exit
			if (mapList[index].walls.size() <= floor(transformComponent.position.y))
				continue;
			else if (mapList[index].walls[floor(transformComponent.position.y)].size() <= transformComponent.position.x)
				continue;
			sf::Vector2u windowSize = cameracomponent.target->getSize();
			for (int x = 0; x < windowSize.x; x++) {
				//cameraX is the x-coordinate in the screen space/ camera space
				float cameraX = 2 * x / float(windowSize.x) - 1;

				sf::Vector2f currentRay = transformComponent.rotation + cameracomponent.plane * (float)cameraX;
				RaycastUtils::RayCollisionInfo collision;
				collision = RaycastUtils::castRay(transformComponent.position, sf::getNormalized(currentRay), mapList[index], cameracomponent.renderDistance);

				if (collision.noHit)
					continue;
				double angleBetween = cos(sf::degToRad(sf::getAngleBetween(transformComponent.rotation, currentRay)));;
				double perpDist;
				if (angleBetween > 0)
					perpDist = collision.perpindcularDistance * angleBetween;
				else perpDist = collision.perpindcularDistance;
				//Draw the lines
				if (perpDist <= 0)
					perpDist = 1;
				int lineHeight = (windowSize.y) / (perpDist);
				int drawStart = (-lineHeight + windowSize.y) / 2;
				int drawEnd = (lineHeight + windowSize.y) / 2;
				int size = drawEnd - drawStart;

				textureSlice.setTexture(&rm.getTexture(mapList[index].wallMapping[collision.tag]));
				sf::Vector2u textSize = textureSlice.getTexture()->getSize();
				int texX = textSize.x * collision.u;
				textureSlice.setSize(sf::Vector2f(textureSlice.getSize().x, lineHeight));
				if ((collision.side == 0 && currentRay.x > 0) || (collision.side == 1 && currentRay.y < 0))
					texX = textSize.x - texX - 1;
				textureSlice.setPosition(x, drawStart);
				textureSlice.setTextureRect(sf::Rect(texX, 0, 1, (int)textSize.y));

				cameracomponent.target->draw(textureSlice);
			}
			cameracomponent.target->display();
		}
	}
	void RenderSystem2D(entt::registry& registry,sf::RenderTexture& renderTarget) {
		//Get the list of entities with this component
		auto view = registry.view<RenderComponent, SpriteComponent, TransformComponent>();
		for (auto entity : view) {
			RenderComponent renderComponent = registry.get<RenderComponent>(entity);
			if (renderComponent.enabled) {
				TransformComponent transformComponent = registry.get<TransformComponent>(entity);
				SpriteComponent& sprite = registry.get<SpriteComponent>(entity);
				sprite.sprite.setPosition(transformComponent.position);
				sprite.sprite.setRotation(sf::getRotationAngle(transformComponent.rotation));
				renderTarget.draw(sprite.sprite, renderComponent.renderStates);
			}
		}
		renderTarget.display();
	}
	
	namespace EntityScriptSystem {
		void OnUpdate(float deltaTime, entt::registry& registry) {
			auto view = registry.view<ScriptComponent>();
			for (auto entity : view) {
				ScriptComponent& script = registry.get<ScriptComponent>(entity);
				script.script->OnUpdate(deltaTime);
			}
		}
		void OnFixedUpdate(float fixedDeltaTime, entt::registry& registry) {
			auto view = registry.view<ScriptComponent>();
			for (auto entity : view) {
				ScriptComponent& script = registry.get<ScriptComponent>(entity);
				script.script->OnFixedUpdate(fixedDeltaTime);
			}
		}
		void OnRender(entt::registry& registry) {
			auto view = registry.view<ScriptComponent>();
			for (auto entity : view) {
				ScriptComponent& script = registry.get<ScriptComponent>(entity);
				script.script->OnRender();
			}
		}
	};
};
