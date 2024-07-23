#include "Camera.h"
Camera::Camera(entt::registry* registry) :Entity(registry) {
	addComponent(TransformComponent());
	this->transformComponent = getComponent<TransformComponent>();
	addComponent(CameraComponent(45.f));
	transformComponent = getComponent<TransformComponent>();
	cameraComponent = getComponent<CameraComponent>();

}
Camera::Camera(entt::registry* registry,sf::Vector2f position, sf::Vector2f rotation) :Entity(registry) {
	addComponent(TransformComponent());
	addComponent(CameraComponent(45.0f));
	cameraComponent = getComponent<CameraComponent>();
	transformComponent = getComponent<TransformComponent>();
	transformComponent->position = position;
	transformComponent->rotation = rotation;
}

void Camera::setPosition(sf::Vector2f position) {
	transformComponent->position = position;
	return;
}
void Camera::setFOV(int FOV) {
	cameraComponent->FOV = FOV;
	cameraComponent->updatePlane();
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

void Camera::setRotation(sf::Vector2f rotation) {
	this->transformComponent->rotation = rotation;
	float mag = sf::getLength(this->cameraComponent->plane);
	this->cameraComponent->plane = sf::getNormalized(sf::getRotated(rotation, -90))*mag;
}
void Camera::setZHeight(float zHeight) {
	cameraComponent->zHeight = zHeight;
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
float Camera::getZHeight() {
	return cameraComponent->zHeight;
}