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
		sf::Vector2f corners[4]={
			sf::Vector2f(transform.position.x , transform.position.y - (size.y / 2.0f)), //Top side
			sf::Vector2f(transform.position.x , transform.position.y + (size.y / 2.0f)), //Bottom side
			sf::Vector2f(transform.position.x - (size.y / 2.0f), transform.position.y), //Left side
			sf::Vector2f(transform.position.x + (size.y / 2.0f), transform.position.y) //Right side
		};
		for (int i = 0; i < 4; i++) {
			if (corners[i].y >= 0 && corners[i].y < mapList[index].walls.size()) {
					if (corners[i].x < 0 && corners[i].x >= mapList[index].walls[(int)corners[i].y].size())
						continue;
					//If the tile is not in the ignore list then resolve collision
					auto iterator = std::find(mapList[index].ignoreCollision.begin(), mapList[index].ignoreCollision.end(), mapList[index].walls[(int)corners[i].y][(int)corners[i].x]);
					if (iterator == mapList[index].ignoreCollision.end())
					{
						sf::Vector2f offSet(0,0);
						if (i == 0)  //Top Collision
							offSet.y = round(corners[i].y) - corners[i].y;
						if (i == 1) //Bottom Collision
							offSet.y = floor(corners[i].y) - corners[i].y;
						if (i == 2) //Left Collision
							offSet.x = round(corners[i].x) - corners[i].x;
						if (i == 3) //Right Collision
							offSet.x = floor(corners[i].x) - corners[i].x;

						transform.position += offSet;

						//Update the corners to the new position
						corners[0] +=offSet;
						corners[1] +=offSet;
						corners[2] +=offSet;
						corners[3] +=offSet;
							
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
		sf::Texture bufferText;
		sf::Image bufferImage,floorImage, ceilImage;
		sf::Image floorText=rm.getTexture("cobble").copyToImage();
		sf::Sprite bufferSprite;
		int prevFloorTag=RAND_MAX, prevCeilingTag = RAND_MAX, prevWallTag = RAND_MAX;
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
			bufferImage.create(windowSize.x, windowSize.y);
			//Floor Casting
			for (int y = (windowSize.y / 2)+1; y < windowSize.y; y++) {
				sf::Vector2f rayDir0 = transformComponent.rotation - (cameracomponent.plane);
				sf::Vector2f rayDir1 = transformComponent.rotation + (cameracomponent.plane);

				int p = y - (windowSize.y / 2);
				float posZ = 0.5f * static_cast<float>(windowSize.y);
				float rowDistance = posZ / static_cast<float>(p);
				sf::Vector2f floorStep =  (rayDir1 - rayDir0)* rowDistance  / static_cast<float>(windowSize.x);
				sf::Vector2f floorPos = transformComponent.position + rowDistance * rayDir0;

				for (int x = 0; x < windowSize.x; x++) {
					sf::Vector2i tileIndex(static_cast<int>(floorPos.x), static_cast<int>(floorPos.y));
					if (tileIndex.y >= mapList[index].floors.size()) {
						continue;
					}
					else if (tileIndex.x >= mapList[index].floors[tileIndex.y].size()) {
						continue;
					}
					if (std::find(mapList[index].ignoreRaycast.begin(), mapList[index].ignoreRaycast.end(), mapList[index].walls[tileIndex.y][tileIndex.x])== mapList[index].ignoreRaycast.end())
						continue;
					int tileFloorTag = mapList[index].floors[tileIndex.y][tileIndex.x];
					int tileCeilingTag = mapList[index].floors[tileIndex.y][tileIndex.x];
					if (tileFloorTag != prevFloorTag) {
						sf::Texture& currentText = rm.getTexture(mapList[index].floorMapping[tileFloorTag]);
						floorImage = currentText.copyToImage();
						prevFloorTag = tileFloorTag;
					}
					if (tileCeilingTag != prevCeilingTag) {
						sf::Texture& currentText = rm.getTexture(mapList[index].ceilingMapping[tileCeilingTag]);
						ceilImage = currentText.copyToImage();
						prevCeilingTag = tileCeilingTag;
					}
					sf::Vector2u floorTextSize = floorImage.getSize();
					sf::Vector2i floorTextIndex(
						static_cast<int>((int)(floorTextSize.x * (floorPos.x - tileIndex.x))),
						static_cast<int>((int)(floorTextSize.y * (floorPos.y - tileIndex.y)))
					);
					if (floorTextIndex.x < 0)
						floorTextIndex.x = floorTextSize.x + floorTextIndex.x;
					else if (floorTextIndex.x >= floorTextSize.x)
						floorTextIndex.x = floorTextIndex.x - floorTextSize.x;
					if (floorTextIndex.y < 0)
						floorTextIndex.y = floorTextSize.y + floorTextIndex.y;
					else if (floorTextIndex.y >= floorTextSize.y)
						floorTextIndex.y = floorTextIndex.y - floorTextSize.y;

					sf::Vector2u ceilTextSize = ceilImage.getSize();
					sf::Vector2i ceilTextIndex(
						static_cast<int>((int)(ceilTextSize.x * (floorPos.x - tileIndex.x))),
						static_cast<int>((int)(ceilTextSize.y * (floorPos.y - tileIndex.y)))
					);
					if (ceilTextIndex.x < 0)
						ceilTextIndex.x = ceilTextSize.x + ceilTextIndex.x;
					else if (ceilTextIndex.x >= ceilTextSize.x)
						ceilTextIndex.x = ceilTextIndex.x - ceilTextSize.x;
					if (ceilTextIndex.y < 0)
						ceilTextIndex.y = floorTextSize.y + ceilTextIndex.y;
					else if (ceilTextIndex.y >= ceilTextSize.y)
						ceilTextIndex.y = ceilTextIndex.y - ceilTextSize.y;

					floorPos = floorPos + floorStep;

					bufferImage.setPixel(x,y, floorImage.getPixel(floorTextIndex.x, floorTextIndex.y));
					bufferImage.setPixel(x, windowSize.y-y-1, ceilImage.getPixel(ceilTextIndex.x, ceilTextIndex.y));
				}
			}
			bufferText.loadFromImage(bufferImage);
			bufferSprite.setTexture(bufferText);
			cameracomponent.target->draw(bufferSprite);
			////////////////////Wall Casting////////////////////////////
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
				if (angleBetween > 0&&!cameracomponent.fisheye)
					perpDist = collision.distance * angleBetween;
				else perpDist = collision.distance;
				//Draw the lines
				float lineHeight = (windowSize.y) / (perpDist);
				float drawStart = (-lineHeight + windowSize.y) / 2;
				float drawEnd = (lineHeight + windowSize.y) / 2;
				float size = drawEnd - drawStart;
				textureSlice.setTexture(&rm.getTexture(mapList[index].wallMapping[collision.tag]));
				sf::Vector2u textSize = textureSlice.getTexture()->getSize();
				int texX = textSize.x * collision.u;
				textureSlice.setSize(sf::Vector2f(textureSlice.getSize().x, lineHeight));
				if ((collision.side == 0 && currentRay.x < 0) || (collision.side == 1 && currentRay.y > 0))
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
