#pragma once
#include "Entity.h"
#include <memory>
/**
* @brief Camera Entity 
* @note Tester entity to see if the ECS situation is working
*/
class Camera :public Entity {
public:
	Camera(entt::registry* registry) ;
	Camera(entt::registry* registry,sf::Vector2f position);

	void setPosition(sf::Vector2f position);
	void setFOV(int FOV);
	void setRenderDistance(float renderDistance);
	void setResolution(sf::Vector2u reslution);
	
	sf::Vector2f getPosition();
	int getFOV();
	float getRenderDistance();
	sf::Vector2u getResolution();
private:
	std::unique_ptr<sf::RenderTexture> perspective;
};