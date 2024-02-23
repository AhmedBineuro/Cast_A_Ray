#pragma once
#define M_PI 3.14159265358979323846
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include <string>
#include <iostream>
#include "SFMLMath.hpp"
#include "Actor.h"
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
        maxSpeed = 30.0f,
        movementMultiplier = 1.0f,
        sprintMultiplier = 2.0f,
        turnAngle = 10.0f;
};