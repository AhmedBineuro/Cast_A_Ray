#pragma once
#define M_PI 3.14159265358979323846
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include <string>
#include <iostream>
#include "SFMLMath.hpp"
//#include "Components.h"
//sf::Vector2f calculatePlane(sf::Vector3f dir, int fov) {
//	 sf::Vector2f plane = sf::Vector2f();
//	 sf::rotate(plane, fov);
//	 float width = (float)tan(fov / 2);
//	 sf::normalize(plane);
//	 plane *= width;
//	 return plane;
//}


struct TransformComponent {
    sf::Vector2f position;
    sf::Vector2f rotation;
    TransformComponent(){}
    TransformComponent(const sf::Vector2f& pos, const sf::Vector2f& rot = sf::Vector2f(0.f, 0.f))
        : position(pos), rotation(rot) {}
};

struct SpriteComponent {
    sf::Sprite sprite;
};

struct RenderComponent {
    sf::RenderWindow* renderWindow;
};

struct CameraComponent {
    int FOV;
    float renderDistance;
    sf::Vector2f plane;
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
    sf::FloatRect border;
    bool solid;
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

class ActorComponent {
public:
    virtual void OnCreate() = 0;
    virtual void OnDestroy() = 0;
    virtual void OnStart() = 0;
    virtual void OnUpdate(float deltaTime) = 0;
    virtual void OnFixedUpdate(float fixedDeltaTime) = 0;
    virtual void OnEnable() = 0;
    virtual void OnDisable() = 0;

    virtual ~ActorComponent() {} // Ensure a virtual destructor for derived classes
};