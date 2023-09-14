#include "Components.h"
sf::Vector2f calculatePlane(sf::Vector3f dir, int fov) {
	 sf::Vector2f plane = sf::Vector2f();
	 sf::rotate(plane, fov);
	 float width = (float)tan(fov / 2);
	 sf::normalize(plane);
	 plane *= width;
	 return plane;
}