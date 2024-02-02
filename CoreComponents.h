#pragma once
#define M_PI 3.14159265358979323846
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include <string>
#include <iostream>
#include "SFMLMath.hpp"
#include "Actor.h"
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