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
    int FOV;
    float renderDistance;
    sf::Vector2f plane;
    sf::RenderTexture* target;
    bool enabled;
    CameraComponent(int fov=90, float distance=400.0f,sf::RenderTexture* targetTexture=nullptr)
        : FOV(fov), renderDistance(distance),target(targetTexture) {
        enabled = true;
        // Add rays = std::make_unique<sf::VertexArray>(...);
        plane=sf::Vector2f(0,0.66f);
        /*float width = (float)tan((float)fov / 2.0f * M_PI / 180.0f);
        sf::normalize(plane);
        plane *= width;*/
    }
};

struct MapTagComponent {
    std::string mapName;
};

struct ColliderComponent {
    sf::FloatRect border;
};