#pragma once
#define M_PI 3.14159265358979323846
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include <string>
#include <iostream>
#include "SFMLMath.hpp"
#include "Engine\include\Actor.h"
#include "Core\include\Map.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include "imgui-knobs.h"
#include "Core\include\Component.h"

extern class Entity;

/*
* @brief Canvas helper struct to assist drag and drop behaviours for assigning canvases
*/
struct Canvas {
    Canvas(std::shared_ptr<sf::RenderTexture> target = nullptr, std::string name = "") :target(target), name(name){}
    std::shared_ptr<sf::RenderTexture> target;
    std::string name;
};

class TransformComponent:public Component {
    
public:
    sf::Vector2f position;
    sf::Vector2f rotation;
    float zLocation=0.5f;
    TransformComponent(const sf::Vector2f& pos=sf::Vector2f(0,0), const sf::Vector2f& rot = sf::Vector2f(1.f, 0.f))
        : position(pos), rotation(rot) {
        componentName = "Transform Component";
    }
};

class IntegratedScriptComponent :public Component {
public:
    bool enabled = true;
    std::vector<std::shared_ptr<Actor>> scripts;
    IntegratedScriptComponent(std::shared_ptr<Actor> script = nullptr) {
        if (script != nullptr)
            this->scripts.push_back(std::move(script));
        else scripts.clear();
        componentName = "IntScript Component";
    }
};
class RenderStatesComponent :public Component  {
public:

    bool enabled;
    sf::RenderStates renderStates;
    RenderStatesComponent() {
        componentName = "RendStates Component";
    }
};

class SpriteComponent :public Component  {
public:

    sf::Sprite sprite;
    SpriteComponent() {
        componentName = "Sprite Component";
    }
};

class ControllableComponent :public Component  {
public:

    bool enabled = true;
    float sensitivity = 1.0,
        maxSpeed = 3.0f,
        movementMultiplier = 0.5f,
        sprintMultiplier = 2.0f,
        turnAngle = 50.0f;
    std::weak_ptr<Entity> test;
    ControllableComponent() {
        componentName = "Controllable Component";
    }
};

class CameraComponent :public Component  {
public:

    float FOV;
    float renderDistance;
    sf::Vector2f plane;
    float tilt;
    std::vector<float> z_buffer;
    bool enabled;

    CameraComponent(float fov = 35.0f, float renderDistance = 10.0f, float tilt = 0.5f)
        : FOV(fov), renderDistance(renderDistance), tilt(tilt) {
        enabled = true;
        updatePlane();
        componentName = "Camera Component";
    }
    void updatePlane() {
        plane = sf::Vector2f(0, -1);
        float width = (float)tan((float)FOV * M_PI / 360.0f);
        sf::normalize(plane);
        plane *= width;
    }

        void setPlaneNormalDirection(sf::Vector2f rotation){
            float mag = sf::getLength(plane);
            plane = sf::getNormalized(sf::getRotated(rotation, -90)) * mag;
        }
};

class MapTagComponent :public Component  {
    public:
        std::string mapName;
        MapTagComponent() {
            componentName = "MapTag Component";
            mapName = "";
        }

        
};

class ColliderComponent :public Component  {
    public:

        sf::FloatRect border;
        bool isTrigger, enabled;
        ColliderComponent(sf::Vector2f position = sf::Vector2f(), sf::Vector2f size = sf::Vector2f(0.5, 0.5)) {
            border = sf::FloatRect(position - (size / 2.0f), size);
            isTrigger = false;
            enabled = true;
            componentName = "Collider Component";
        }
};

class CanvasComponent :public Component {
public:
    std::string canvasName;
    std::weak_ptr<sf::RenderTexture> canvas;

    CanvasComponent(std::string name = "", std::shared_ptr<sf::RenderTexture> canvas = nullptr) :canvasName(name), canvas(std::weak_ptr(canvas)) {
        this->componentName = "Canvas Component";
    }
};
class BillBoardComponent :public Component {
public:
    float height;
    sf::Sprite sprite;
    bool enabled;
};