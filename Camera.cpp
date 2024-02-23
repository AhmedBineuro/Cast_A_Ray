#include "Camera.h"
Camera::Camera(entt::registry* registry) :Entity2D(registry) {
	transformComponent = getComponent<TransformComponent>();
	CameraComponent camera = CameraComponent(90, 100);
	cameraComponent = getComponent<CameraComponent>();
	addComponent(camera);

}
Camera::Camera(entt::registry* registry,sf::Vector2f position) :Entity2D(registry) {
	transformComponent = getComponent<TransformComponent>();
	CameraComponent camera = CameraComponent();
	addComponent(camera);
	cameraComponent = getComponent<CameraComponent>();
}

void Camera::setPosition(sf::Vector2f position) {
	transformComponent->position = position;
	spriteComponent->sprite.setPosition(position);
	return;
}
void Camera::setFOV(int FOV) {
	cameraComponent->FOV = FOV;
	return;
}
void Camera::setRenderDistance(float renderDistance) {
	cameraComponent->renderDistance= renderDistance;
	return;
}
void Camera::setAngleRAD(float angle) {
	setAngleDEG(sf::degToRad(sf::radToDeg(angle)));
	return;
}
void Camera::setAngleDEG(float angle) {
	transformComponent->rotation = sf::getRotated(sf::Vector2f(1.0f, 0.f),angle);
	cameraComponent->plane = sf::getRotated(transformComponent->rotation, 90);
	return;
}

void Camera::linkRenderTarget(sf::RenderTexture* renderTexture) {
	cameraComponent->target = renderTexture;
}
void Camera::setEnabled(bool value) {
	cameraComponent->enabled = value;
}

sf::Vector2f Camera::getPosition() {
	return getComponent<TransformComponent>()->position;
}
int Camera::getFOV() {
	return getComponent<CameraComponent>()->FOV;
}
float Camera::getRenderDistance() {
	return getComponent<CameraComponent>()->renderDistance;
}