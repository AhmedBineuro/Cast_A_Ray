#pragma once
#include "Entity.h"
#include <memory>
/**
* @brief Camera Entity 
* @note Tester entity to see if the ECS situation is working
*/
class Camera :public Entity {
public:
	Camera() ;
	Camera(sf::Vector3f position, sf::Vector3f direction);

	void setPosition(sf::Vector3f position);
	void setDirection(sf::Vector3f direction);
	void setFOV(int FOV);
	void setRenderDistance(float renderDistance);
	void setResolution(sf::Vector2u reslution);
	
	sf::Vector3f getPosition();
	sf::Vector3f getDirection();
	int getFOV();
	float getRenderDistance();
	sf::Vector2u getResolution();

	void linkMap(map_tag_component mapTag);
	void unlinkMap();
private:
	std::unique_ptr<sf::RenderTexture> perspective;
};