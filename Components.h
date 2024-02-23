#pragma once
#define M_PI 3.14159265358979323846
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include <string>
#include <iostream>
#include "SFMLMath.hpp"
#include "Actor.h"
//#include "Components.h"
//sf::Vector2f calculatePlane(sf::Vector3f dir, int fov) {
//	 sf::Vector2f plane = sf::Vector2f();
//	 sf::rotate(plane, fov);
//	 float width = (float)tan(fov / 2);
//	 sf::normalize(plane);
//	 plane *= width;
//	 return plane;
//}




struct CameraComponent {
    int FOV;
    float renderDistance;
    sf::Vector2f plane;
    bool enabled;
    CameraComponent() {
        FOV = 90;
        renderDistance = 100;
        sf::rotate(plane, sf::getRotationAngle(sf::Vector2f(0,-1)));
        float width = (float)tan(FOV / 2 * M_PI / 180.0f);
        sf::normalize(plane);
        plane *= width;
    }
    CameraComponent(int fov, float distance)
        : FOV(fov), renderDistance(distance) {
        // Add rays = std::make_unique<sf::VertexArray>(...);
        sf::rotate(plane, sf::getRotationAngle(sf::Vector2f(0, -1)));
        float width = (float)tan(fov / 2 * M_PI / 180.0f);
	    sf::normalize(plane);
	    plane *= width;
    }
};

struct ColliderComponent {
    sf::FloatRect bounds;
    bool solid;
    std::string tag;
    ColliderComponent(){
        bounds = sf::FloatRect(sf::Vector2f(0, 0), sf::Vector2f(1, 1));
        solid = false;
        tag = "";
    }
    ColliderComponent(const sf::FloatRect& bounds, bool isSolid, const std::string& tag)
        : bounds(bounds), solid(isSolid), tag(tag) {}
};

struct AudioSourceComponent {
    std::shared_ptr<sf::Sound> audioClip;
};

struct AudioListenerComponent {
    sf::Vector3f position;
    sf::Vector3f direction; // Forward direction
    sf::Vector3f upVector;  // Upward direction, typically (0, 1, 0)

    void apply() {
        sf::Listener::setPosition(position);
        sf::Listener::setDirection(direction);
        sf::Listener::setUpVector(upVector);
    }
};

struct EntityTagComponent {
    std::string tag;
};