#include "Camera.h"
Camera::Camera() :Entity() {
	addComponent(position_component());
	addComponent(perspective_component(sf::Vector3f(0,1,0),90,100));
	perspective = std::make_unique<sf::RenderTexture>();
	if (!perspective->create(800, 800)) {
		std::cerr << "Could not create camera render texture" << std::endl;
	}

}
Camera::Camera(sf::Vector3f position,sf::Vector3f direction) :Entity() {
	addComponent(position_component(position));
	addComponent(perspective_component(direction, 90, 100));
	perspective = std::make_unique<sf::RenderTexture>();
	if (!perspective->create(800, 800)) {
		std::cerr << "Could not create camera render texture" << std::endl;
	}
}

void Camera::setPosition(sf::Vector3f position) {
	position_component* pos = getComponent<position_component>();
	pos->literal_position = position;
	return;
}
void Camera::setDirection(sf::Vector3f direction) {
	perspective_component* perp = getComponent<perspective_component>();
	perp->direction = direction;
	return;
}
void Camera::setFOV(int FOV) {
	perspective_component* perp = getComponent<perspective_component>();
	perp->FOV = FOV;
	return;
}
void Camera::setRenderDistance(float renderDistance) {
	perspective_component* perp = getComponent<perspective_component>();
	perp->render_distance= renderDistance;
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
	return getComponent<position_component>()->literal_position;
}
sf::Vector2f Camera::getDirection() {
	return getComponent<perspective_component>()->direction;
}
int Camera::getFOV() {
	return getComponent<perspective_component>()->FOV;
}
float Camera::getRenderDistance() {
	return getComponent<perspective_component>()->render_distance;
}
sf::Vector2u Camera::getResolution() {
	return perspective->getSize();
}

void Camera::linkMap(map_tag_component mapTag) {
	if (hasComponent<map_tag_component>())
	{
		replaceComponent(mapTag);
	}
	else {
		addComponent(mapTag);
	}
}
void Camera::unlinkMap() {
	if (hasComponent<map_tag_component>()) {
		removeComponent<map_tag_component>();
	}
}