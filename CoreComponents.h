#pragma once
#define M_PI 3.14159265358979323846
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include <string>
#include <iostream>
#include "SFMLMath.hpp"
#include "Actor.h"
#include "Map.h"
struct TransformComponent {
    sf::Vector2f position;
    sf::Vector2f rotation;
    TransformComponent() {}
    TransformComponent(const sf::Vector2f& pos, const sf::Vector2f& rot = sf::Vector2f(1.f, 0.f))
        : position(pos), rotation(rot) {}
};
struct ScriptComponent {
    std::shared_ptr<Actor> script;
    ScriptComponent(std::shared_ptr<Actor> script) : script(std::move(script)) {}
};
struct RenderComponent {
    bool enabled;
    sf::RenderStates renderStates;
};

struct SpriteComponent {
    sf::Sprite sprite;
};

struct ControllableComponet {
    bool enabled=true;
    float sensitivity = 1.0,
        maxSpeed = 0.5f,
        movementMultiplier = 1.0f,
        sprintMultiplier = 2.0f,
        turnAngle = 50.0f;
};

struct CameraComponent {
    float FOV;
    float renderDistance;
    sf::Vector2f plane;
    sf::RenderTexture* target;
    float zHeight;
    bool enabled,fisheye=false;

    CameraComponent(float fov=90.0f, float renderDistance=10.0f,sf::RenderTexture* targetTexture=nullptr, float zHeight= 0.5f)
        : FOV(fov), renderDistance(renderDistance),target(targetTexture), zHeight(zHeight){
        enabled = true;
        // Add rays = std::make_unique<sf::VertexArray>(...);
        updatePlane();
    }
    void updatePlane() {
        plane = sf::Vector2f(1, 1);
        float width = (float)tan((float)FOV * M_PI / 360.0f);
        sf::normalize(plane);
        plane *= width;
    }
};

struct MapTagComponent {
    std::string mapName;
};

struct ColliderComponent {
    sf::FloatRect border;
    bool isTrigger,enabled;
    ColliderComponent(sf::Vector2f position=sf::Vector2f(),sf::Vector2f size= sf::Vector2f(5,5)) {
        border = sf::FloatRect(position-(size/2.0f), size);
        isTrigger = false;
        enabled = true;
    }
};