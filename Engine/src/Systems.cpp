#include "Engine\include\Systems.h"
namespace Systems {

	namespace CollisionSystem {
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
				//TODO Change from sides to corners or something because it is skipping checks
				sf::Vector2f sides[4] = {
					sf::Vector2f(transform.position.x , transform.position.y - (size.y / 2.0f)), //Top side
					sf::Vector2f(transform.position.x , transform.position.y + (size.y / 2.0f)), //Bottom side
					sf::Vector2f(transform.position.x - (size.x / 2.0f), transform.position.y), //Left side
					sf::Vector2f(transform.position.x + (size.x / 2.0f), transform.position.y) //Right side
				};
				for (int i = 0; i < 4; i++) {
					if ((int)sides[i].y >= 0 && (int)sides[i].y < currentMap.walls.size() &&
						(int)sides[i].x >= 0 && (int)sides[i].x < currentMap.walls[(int)sides[i].y].size()) {
						//If the tile is not in the ignore list then resolve collision
						auto iterator = std::find(currentMap.ignoreCollision.begin(), currentMap.ignoreCollision.end(), currentMap.walls[(int)sides[i].y][(int)sides[i].x]);
						if (iterator == currentMap.ignoreCollision.end())
						{
							sf::Vector2f offSet(0, 0);
							if (i == 0)  //Top Collision
								offSet.y = round(sides[i].y) - sides[i].y;
							if (i == 1) //Bottom Collision
								offSet.y = floor(sides[i].y) - sides[i].y;
							if (i == 2) //Left Collision
								offSet.x = round(sides[i].x) - sides[i].x;
							if (i == 3) //Right Collision
								offSet.x = floor(sides[i].x) - sides[i].x;

							transform.position += offSet;

							//Update the sides to the new position
							
							for (int j = i + 1; j < 4;j++)
								sides[j] += offSet;
						}
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
				sf::VertexArray skybox=sf::VertexArray(sf::Quads,8);
				sf::Color top = sf::Color(190, 190, 226);
				sf::Color mid = sf::Color(100, 100, 100);
				sf::Color bot = sf::Color::Black;
				skybox[0].color = top;
				skybox[1].color = top;
				skybox[2].color = mid;
				skybox[3].color = mid;
				skybox[4].color = mid;
				skybox[5].color = mid;
				skybox[6].color = bot;
				skybox[7].color = bot;

				auto view = registry.view<CameraComponent, TransformComponent,CanvasComponent>();
				for (auto entity : view) {
					CameraComponent& cameracomponent = registry.get<CameraComponent>(entity);
					CanvasComponent& canvascomponent = registry.get<CanvasComponent>(entity);
					auto canvas = canvascomponent.canvas.lock();
					if (!cameracomponent.enabled || !canvas)
						continue;
					TransformComponent& transformComponent = registry.get<TransformComponent>(entity);

					sf::Vector2u windowSize = canvas->getSize();
					sf::Image floorNceil;
					sf::Texture floorsText;
					floorNceil.create(windowSize.x, windowSize.y,sf::Color::Transparent);
					
					////////////////////Wall Casting////////////////////////////
					skybox[0].position = sf::Vector2f(0,0);
					skybox[1].position = sf::Vector2f(windowSize.x, 0);
					skybox[2].position = sf::Vector2f(windowSize.x, windowSize.y * cameracomponent.zHeight);
					skybox[3].position = sf::Vector2f(0, windowSize.y * cameracomponent.zHeight);
					skybox[4].position = sf::Vector2f(0, windowSize.y * cameracomponent.zHeight);
					skybox[5].position = sf::Vector2f(windowSize.x, windowSize.y * cameracomponent.zHeight);
					skybox[6].position = sf::Vector2f(windowSize.x, windowSize.y);
					skybox[7].position = sf::Vector2f(0, windowSize.y);
					canvas->draw(skybox);
					for (int x = 0; x < windowSize.x; x++) {
						//cameraX is the x-coordinate in the screen space/ camera space
						float cameraX = 2 * x / float(windowSize.x) - 1;

						sf::Vector2f currentRay = sf::getNormalized(transformComponent.rotation) + cameracomponent.plane * (float)cameraX;
						RaycastUtils::RayCollisionInfo collision;
						collision = RaycastUtils::castRay(transformComponent.position, currentRay, currentMap, cameracomponent.renderDistance);
						float lineHeight = 0;
						double perpDist= cameracomponent.renderDistance;
						if (!collision.noHit)
						{
							perpDist = collision.distance;
							//Draw the lines
							lineHeight = (windowSize.y) / (perpDist);
						}
						float drawStart = -(lineHeight * 0.5f) + (windowSize.y * cameracomponent.zHeight);
						float drawEnd= (lineHeight * 0.5f) + (windowSize.y * cameracomponent.zHeight);
						if(!collision.noHit)
						{
							std::string textName = currentMap.wallMapping[collision.tag];
							sf::Texture* text = nullptr;
							Graphics_Helper::addTexture(textName);
							text = Graphics_Helper::TextureCache[textName];
							textureSlice.setTexture(text);
							sf::Vector2u textSize = text->getSize();
							int texX = textSize.x * collision.u;
							textureSlice.setTextureRect(sf::Rect(texX, 0, 1, (int)textSize.y));
							if ((collision.side == 0 && currentRay.x < 0) || (collision.side == 1 && currentRay.y > 0))
								texX = textSize.x - texX - 1;
						}
						textureSlice.setSize(sf::Vector2f(textureSlice.getSize().x, lineHeight));
						textureSlice.setPosition(x, drawStart);
						float amount = floor(sf::lerp(255,0, perpDist / cameracomponent.renderDistance));
						sf::Color shade = sf::Color( amount, amount, amount);
						textureSlice.setFillColor(shade);
						canvas->draw(textureSlice);

						sf::Vector2f newRay = sf::getNormalized(currentRay);
						float distToPlane = sf::getLength(transformComponent.rotation);
						//Floor Rendering
						for (int y = drawEnd+1; y < windowSize.y; y++) {
							float normalizedYFloor = float(y) / float(windowSize.y);
							//@TODO Replace 0.5f with the actual player's vertical position
							float distToCollision = 0.5f* (distToPlane / (normalizedYFloor - cameracomponent.zHeight));
							sf::Vector2f floorPosition = transformComponent.position + (newRay * distToCollision);
							sf::Vector2f tilePosition = sf::floor(floorPosition);
							sf::Vector2f uv = floorPosition-tilePosition;
							sf::Color c1;
							if (tilePosition.y >= 0 && tilePosition.y < currentMap.floors.size() && tilePosition.x >= 0 && tilePosition.x < currentMap.floors[floorPosition.y].size()) {
								int tag = currentMap.floors[floorPosition.y][floorPosition.x];
								sf::Image& imF=rm.getImage(currentMap.floorMapping[tag]);
								sf::Vector2i textIndex = sf::Vector2i(floor(uv.x * imF.getSize().x), 
									floor(uv.y * imF.getSize().y));
								c1 = imF.getPixel(textIndex.x, textIndex.y);
							}
							else {
								if (uv.x < 0.02f || uv.x>0.98f || uv.y < 0.02f || uv.y>0.98f)
									c1 = sf::Color(0,0,0,80);
								else c1 = sf::Color(255, 255, 255, 80);
							}
							c1 = sf::mix(c1, sf::Color::Black, sf::getClamped(distToCollision / cameracomponent.renderDistance, 0.0f, 1.0f), false);
							if(x>=0&&x<floorNceil.getSize().x
								&& y >= 0 && y < floorNceil.getSize().y)
								floorNceil.setPixel(x, y, c1);
						}
						//Ceil Rendering
						for (int y = 0; y < drawStart; y++) {
							float normalizedY = float(y) / float(windowSize.y);
							//@TODO Replace 0.5f with the actual player's vertical position
							float distToCollision = abs(0.5f * (distToPlane / (normalizedY - cameracomponent.zHeight)));
							sf::Vector2f floorPosition = transformComponent.position + (newRay * distToCollision);
							sf::Vector2f tilePosition = sf::floor(floorPosition);
							sf::Vector2f uv = floorPosition - tilePosition;
							sf::Color c;
							if (tilePosition.y >= 0 && tilePosition.y < currentMap.ceilings.size() && tilePosition.x >= 0 && tilePosition.x < currentMap.ceilings[floorPosition.y].size()) {
								int tag = currentMap.ceilings[floorPosition.y][floorPosition.x];
								sf::Image& im = rm.getImage(currentMap.ceilingMapping[tag]);
								sf::Vector2i textIndex = sf::Vector2i(floor(uv.x * im.getSize().x),
									floor(uv.y * im.getSize().y));
								c = im.getPixel(textIndex.x, textIndex.y);
							}
							else {
								if (uv.x < 0.02f || uv.x>0.98f || uv.y < 0.02f || uv.y>0.98f)
									c = sf::Color(0, 0, 0, 80);
								else c = sf::Color(255, 255, 255, 80);
							}
							float shadeR = sf::lerp(c.r, 0, (sf::getClamped(distToCollision / cameracomponent.renderDistance, 0.0f, 1.0f)));
							float shadeG = sf::lerp(c.g, 0, (sf::getClamped(distToCollision / cameracomponent.renderDistance, 0.0f, 1.0f)));
							float shadeB = sf::lerp(c.b, 0, (sf::getClamped(distToCollision / cameracomponent.renderDistance, 0.0f, 1.0f)));
							c = sf::Color(shadeR, shadeG, shadeB);
							if (x >= 0 && x < floorNceil.getSize().x
								&& y >= 0 && y < floorNceil.getSize().y)
								floorNceil.setPixel(x, y, c);
						}

					}
					sf::Sprite floors=sf::Sprite();
					floors.setPosition(0, 0);
					floorsText.loadFromImage(floorNceil);
					floors.setTexture(floorsText);
					
					canvas->draw(floors);
				}
			}
			void renderFloors(entt::registry& registry, Map& currentMap) {
			 //Tutorial at:
			 // https://permadi.com/1996/05/ray-casting-tutorial-11/
			}
	}




	void RenderSystem2D(entt::registry& registry,sf::RenderTexture& renderTarget) {
		//Get the list of entities with this component
		auto view = registry.view<RenderStatesComponent, SpriteComponent, TransformComponent>();
		for (auto entity : view) {
			RenderStatesComponent& renderStatesComponent = registry.get<RenderStatesComponent>(entity);
			if (renderStatesComponent.enabled) {
				TransformComponent& transformComponent = registry.get<TransformComponent>(entity);
				SpriteComponent& sprite = registry.get<SpriteComponent>(entity);
				sprite.sprite.setPosition(transformComponent.position*50.0f);
				sprite.sprite.setRotation(sf::getRotationAngle(transformComponent.rotation));
				renderTarget.draw(sprite.sprite, renderStatesComponent.renderStates);
			}
		}
		renderTarget.display();
	}
	
	namespace EntityScriptSystem {
		void OnUpdate(float deltaTime, entt::registry& registry) {
			auto view = registry.view<IntegratedScriptComponent>();
			for (auto entity : view) {
				IntegratedScriptComponent& scripts = registry.get<IntegratedScriptComponent>(entity);
				for (auto script : scripts.scripts)
					if (script->enabled)
						script->OnUpdate(deltaTime);
			}
		}
		void OnFixedUpdate(float fixedDeltaTime, entt::registry& registry) {
			auto view = registry.view<IntegratedScriptComponent>();
			for (auto entity : view) {
				IntegratedScriptComponent& scripts = registry.get<IntegratedScriptComponent>(entity);
				for (auto script : scripts.scripts)
					if (script->enabled)
						script->OnFixedUpdate(fixedDeltaTime);
			}
		}
		void OnRender(entt::registry& registry) {
			auto view = registry.view<IntegratedScriptComponent>();
			for (auto entity : view) {
				IntegratedScriptComponent& scripts = registry.get<IntegratedScriptComponent>(entity);
				for(auto script:scripts.scripts)
					if (script->enabled)
						script->OnRender();
			}
		}
		void OnEventLoop(entt::registry& registry, sf::Event event) {
			auto view = registry.view<IntegratedScriptComponent>();
			for (auto entity : view) {
				IntegratedScriptComponent& scripts = registry.get<IntegratedScriptComponent>(entity);
				for (auto script : scripts.scripts)
					if (script->enabled)
						script->OnEventLoop(event);
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