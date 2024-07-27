#include "Systems.h"
namespace Systems {

	void WolfCollisionSystem(entt::registry& registry, Map& currentMap) {
	auto view = registry.view<ColliderComponent, TransformComponent>();
		for (auto entity : view) {
			//Check Collision against map tiles using aabb
			ColliderComponent& collider = registry.get<ColliderComponent>(entity);
			TransformComponent& transform = registry.get<TransformComponent>(entity);
			sf::Vector2f size = collider.border.getSize();
			if (!collider.enabled)
				continue;
			//Check the borders
			sf::Vector2f corners[4]={
				sf::Vector2f(transform.position.x , transform.position.y - (size.y / 2.0f)), //Top side
				sf::Vector2f(transform.position.x , transform.position.y + (size.y / 2.0f)), //Bottom side
				sf::Vector2f(transform.position.x - (size.y / 2.0f), transform.position.y), //Left side
				sf::Vector2f(transform.position.x + (size.y / 2.0f), transform.position.y) //Right side
			};
			for (int i = 0; i < 4; i++) {
				if ((int)corners[i].y >= 0 && (int)corners[i].y < currentMap.walls.size() &&
					(int)corners[i].x >= 0 && (int)corners[i].x < currentMap.walls[(int)corners[i].y].size()) {
						//If the tile is not in the ignore list then resolve collision
						auto iterator = std::find(currentMap.ignoreCollision.begin(), currentMap.ignoreCollision.end(), currentMap.walls[(int)corners[i].y][(int)corners[i].x]);
						if (iterator == currentMap.ignoreCollision.end())
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
	namespace DDARenderSystem {
			void renderWalls(entt::registry& registry, Map& currentMap)
			{
				Config& config = Config::getConfig();
				Resource_Manager& rm = Resource_Manager::getResourceManager();
				sf::RectangleShape textureSlice(sf::Vector2f(1, 10));
				int prevFloorTag = RAND_MAX, prevCeilingTag = RAND_MAX, prevWallTag = RAND_MAX;
				auto view = registry.view<CameraComponent, TransformComponent>();
				for (auto entity : view) {
					CameraComponent& cameracomponent = registry.get<CameraComponent>(entity);
					if (!cameracomponent.enabled || cameracomponent.target==nullptr)
						continue;
					TransformComponent& transformComponent = registry.get<TransformComponent>(entity);
					sf::Vector2u windowSize = cameracomponent.target->getSize();
					////////////////////Wall Casting////////////////////////////
					for (int x = 0; x < windowSize.x; x++) {
						//cameraX is the x-coordinate in the screen space/ camera space
						float cameraX = 2 * x / float(windowSize.x) - 1;

						sf::Vector2f currentRay = transformComponent.rotation + cameracomponent.plane * (float)cameraX;
						RaycastUtils::RayCollisionInfo collision;
						collision = RaycastUtils::castRay(transformComponent.position, sf::getNormalized(currentRay), currentMap, cameracomponent.renderDistance);

						if (collision.noHit)
							continue;
						double angleBetween = cos(sf::degToRad(sf::getAngleBetween(transformComponent.rotation, currentRay)));;
						double perpDist;
						if (angleBetween > 0 && !cameracomponent.fisheye)
							perpDist = collision.distance * angleBetween;
						else perpDist = collision.distance;
						//Draw the lines
						float lineHeight = (windowSize.y) / (perpDist);
						float drawStart = (-lineHeight + windowSize.y) * cameracomponent.zHeight;
						float drawEnd = (lineHeight + windowSize.y) * cameracomponent.zHeight;
						float size = drawEnd - drawStart;
						std::string textName = currentMap.wallMapping[collision.tag];
						sf::Texture* text = nullptr;
						Graphics_Helper::addTexture(textName);
						text = Graphics_Helper::TextureCache[textName];
						textureSlice.setTexture(text);
						sf::Vector2u textSize = text->getSize();
						int texX = textSize.x * collision.u;
						textureSlice.setSize(sf::Vector2f(textureSlice.getSize().x, lineHeight));
						if ((collision.side == 0 && currentRay.x < 0) || (collision.side == 1 && currentRay.y > 0))
							texX = textSize.x - texX - 1;
						textureSlice.setPosition(x, drawStart);
						textureSlice.setTextureRect(sf::Rect(texX, 0, 1, (int)textSize.y));
						float amount = perpDist / cameracomponent.renderDistance;
						sf::Color shade = sf::Color(255 * (1 - amount), 255 * (1 - amount), 255 * (1 - amount));
						textureSlice.setFillColor(shade);
						cameracomponent.target->draw(textureSlice);
					}
					cameracomponent.target->display();
				}
			}
			void renderFloors(entt::registry& registry, Map& currentMap) {

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
				sprite.sprite.setPosition(transformComponent.position*50.0f);
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
				if(script.enabled)
					script.script->OnUpdate(deltaTime);
			}
		}
		void OnFixedUpdate(float fixedDeltaTime, entt::registry& registry) {
			auto view = registry.view<ScriptComponent>();
			for (auto entity : view) {
				ScriptComponent& script = registry.get<ScriptComponent>(entity);
				if (script.enabled)
					script.script->OnFixedUpdate(fixedDeltaTime);
			}
		}
		void OnRender(entt::registry& registry) {
			auto view = registry.view<ScriptComponent>();
			for (auto entity : view) {
				ScriptComponent& script = registry.get<ScriptComponent>(entity);
				if (script.enabled)
					script.script->OnRender();
			}
		}
		void OnEventLoop(entt::registry& registry, sf::Event event) {
			auto view = registry.view<ScriptComponent>();
			for (auto entity : view) {
				ScriptComponent& script = registry.get<ScriptComponent>(entity);
				if (script.enabled)
					script.script->OnEventLoop(event);
			}
		}
	};
};
namespace Graphics_Helper {
	//Returns true if found in cache
	bool checkImage(std::string name) {
		return (Graphics_Helper::ImageCache.find(name) != Graphics_Helper::ImageCache.end());
	}

	//Returns true if found in cache
	bool checkTexture(std::string name) {
		return (Graphics_Helper::TextureCache.find(name) != Graphics_Helper::TextureCache.end());
	}

	void addTexture(std::string name) {
		Resource_Manager& rm = Resource_Manager::getResourceManager();
		if (!checkTexture(name))
			Graphics_Helper::TextureCache[name] = &rm.getTexture(name);
	}
	void addImage(std::string name) {
		Resource_Manager& rm = Resource_Manager::getResourceManager();
		if (!checkImage(name))
		{
			addTexture(name);
			Graphics_Helper::ImageCache[name] = rm.getImage(name);
		}
	}
}