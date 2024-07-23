#pragma once
#include "Entity.h"
#include "CoreComponents.h"
#include <memory>
/**
* @brief Camera Entity 
* @note Tester entity to see if the ECS situation is working
*/
class Camera :public Entity {
public:
	Camera(entt::registry* registry) ;
	Camera(entt::registry* registry,sf::Vector2f position,sf::Vector2f rotation=sf::Vector2f(1,0));

	void setPosition(sf::Vector2f position);
	void setFOV(int FOV);
	void setRenderDistance(float renderDistance);
	void setAngleRAD(float angle); //Absolute rotation
	void setAngleDEG(float angle);
	void setRotation(sf::Vector2f rotation);
	void setZHeight(float zHeight);
	void linkRenderTarget(sf::RenderTexture* renderTexture);
	void setEnabled(bool value);

	sf::Vector2f getPosition();
	int getFOV();
	float getRenderDistance();
	float getZHeight();
protected:
	CameraComponent* cameraComponent;
	TransformComponent* transformComponent;
};