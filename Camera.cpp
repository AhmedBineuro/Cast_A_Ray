#include "Camera.h"
Camera::Camera(entt::registry* registry) :Entity(registry) {
	TransformComponent transform = TransformComponent();
	addComponent(transform);
	CameraComponent camera = CameraComponent(90, 100);
	addComponent(camera);
	perspective = std::make_unique<sf::RenderTexture>();
	if (!perspective->create(800, 800)) {
		std::cerr << "Could not create camera render texture" << std::endl;
	}

}
Camera::Camera(entt::registry* registry,sf::Vector2f position) :Entity(registry) {
	TransformComponent transform = TransformComponent(position);
	addComponent(transform);
	CameraComponent camera = CameraComponent();
	addComponent(camera);
	perspective = std::make_unique<sf::RenderTexture>();
	if (!perspective->create(800, 800)) {
		std::cerr << "Could not create camera render texture" << std::endl;
	}
}

void Camera::setPosition(sf::Vector2f position) {
	TransformComponent* pos = getComponent<TransformComponent>();
	pos->position = position;
	return;
}
void Camera::setFOV(int FOV) {
	CameraComponent* perp = getComponent<CameraComponent>();
	perp->FOV = FOV;
	return;
}
void Camera::setRenderDistance(float renderDistance) {
	CameraComponent* perp = getComponent<CameraComponent>();
	perp->renderDistance= renderDistance;
	return;
}
void Camera::setResolution(sf::Vector2u reslution) {
	sf::Sprite temp(perspective->getTexture());
	auto newT= std::make_unique<sf::RenderTexture>();;
	if (!newT->create(reslution.x, reslution.y)) {
		std::cerr << "Could not create camera render texture" << std::endl;
	}
	newT->clear();
	newT->draw(temp);
	newT->display();
	perspective = std::move(newT);
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
sf::Vector2u Camera::getResolution() {
	return perspective->getSize();
}