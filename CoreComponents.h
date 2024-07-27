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
#include "imgui.h"
#include "imgui-SFML.h"

class Component {
public:
    virtual void draw() {};
    std::string componentName;
};

class TransformComponent:public Component {
    
public:
    sf::Vector2f position;
    sf::Vector2f rotation;
    TransformComponent(const sf::Vector2f& pos=sf::Vector2f(0,0), const sf::Vector2f& rot = sf::Vector2f(1.f, 0.f))
        : position(pos), rotation(rot) {
        componentName = "Transform";
    }
    void draw() {
        if (ImGui::CollapsingHeader("Transform Component")) {
            ImGui::Indent();
            ImGui::Text("Position: ");
            ImGui::InputFloat("X##Pos", &position.x);
            ImGui::InputFloat("Y##Pos", &position.y);
            
            ImGui::Text("Rotation: ");
            ImGui::InputFloat("X##Rot", &rotation.x);
            ImGui::InputFloat("Y##Rot", &rotation.y);
            ImGui::Unindent();
        }
    };
};

class ScriptComponent: public Component {
public:
    bool enabled = true;
    std::shared_ptr<Actor> script;
    ScriptComponent(std::shared_ptr<Actor> script) : script(std::move(script)) {
        componentName = "Script";
    }
    void draw() {
        if (ImGui::CollapsingHeader("Script Component")) {
            ImGui::Indent();
            script->renderImGui();
            ImGui::Checkbox("Enabled##script",&enabled);
            ImGui::Unindent();
        }
    };
};
class RenderComponent : public Component {
public:

    bool enabled;
    sf::RenderStates renderStates;
    RenderComponent() {
        componentName = "Render";
    }
    void draw() {
        if (ImGui::CollapsingHeader("Render Component")) {
            ImGui::Indent();
            ImGui::Checkbox("Enabled##Render", &enabled);
            ImGui::Unindent();
        }
    };
};

class SpriteComponent : public Component {
public:

    sf::Sprite sprite;
    SpriteComponent() {
        componentName = "Sprite";
    }
    void draw() {
        if (ImGui::CollapsingHeader("Sprite Component")) {
            ImGui::Indent();
            ImGui::Unindent();
        }
    };
};

class ControllableComponent : public Component {
public:

    bool enabled = true;
    float sensitivity = 1.0,
        maxSpeed = 0.5f,
        movementMultiplier = 1.0f,
        sprintMultiplier = 2.0f,
        turnAngle = 50.0f;
    ControllableComponent() {
        componentName = "Controllable";
    }
    void draw() {
        if (ImGui::CollapsingHeader("Controllable Component")) {
            ImGui::Indent();
            ImGui::Checkbox("Enabled##Controllable", &enabled);

            ImGui::InputFloat("Max Speed", &maxSpeed);

            ImGui::InputFloat("Movement Multiplier", &movementMultiplier);

            ImGui::InputFloat("Sprint Multiplier", &sprintMultiplier);

            ImGui::InputFloat("Turn angle", &turnAngle);
            
            ImGui::InputFloat("Sensitivity", &sensitivity);
            ImGui::Unindent();
        }
    };
};

class CameraComponent : public Component {
public:

    float FOV;
    float renderDistance;
    sf::Vector2f plane;
    sf::RenderTexture* target;
    float zHeight;
    bool enabled, fisheye = false;

    CameraComponent(float fov = 35.0f, float renderDistance = 10.0f, sf::RenderTexture* targetTexture = nullptr, float zHeight = 0.5f)
        : FOV(fov), renderDistance(renderDistance), target(targetTexture), zHeight(zHeight) {
        enabled = true;
        updatePlane();
        componentName = "Camera";
    }
    void updatePlane() {
        plane = sf::Vector2f(1, 1);
        float width = (float)tan((float)FOV * M_PI / 360.0f);
        sf::normalize(plane);
        plane *= width;
    }

    void draw() {
        if (ImGui::CollapsingHeader("Camera Component")) {
            if (ImGui::BeginDragDropTarget()) {
                if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("_RNDR_TRGT_PTR_")) {
                    std::weak_ptr<sf::RenderTexture> wptr = std::weak_ptr<sf::RenderTexture>(*static_cast<std::shared_ptr<sf::RenderTexture>*>(payload->Data));
                    if (!wptr.lock())
                    {
                        printf("Bad Texture\n");
                    }
                    else {
                        target = wptr.lock().get();
                    }
                    printf("Valid text: %d\n", target->getSize().x);
                    ImGui::Text("Target Assigned");
                    ImGui::EndDragDropTarget();
                }
                ImGui::Text("Target Assigned: %s", (target == nullptr) ? "No" : "Yes");
                ImGui::Unindent();
            }
            ImGui::Indent();
            ImGui::Text("Plane: x:%f , y:%f", plane.x, plane.y);


            if (ImGui::InputFloat("FOV", &FOV)) {
                updatePlane();
            }

            ImGui::InputFloat("Render Distance", &renderDistance);

            ImGui::InputFloat("Vertical Height", &zHeight);

            ImGui::Checkbox("Fisheye", &fisheye);

            ImGui::Checkbox("Enable##Camera", &enabled);
        }
    }
        void setPlaneNormalDirection(sf::Vector2f rotation){
            float mag = sf::getLength(plane);
            plane = sf::getNormalized(sf::getRotated(rotation, -90)) * mag;
        }
};

class MapTagComponent : public Component {
    public:
        std::string mapName;
        MapTagComponent() {
            componentName = "Map Tag";
            mapName = "";
        }

        //void draw() {
        //    if (ImGui::CollapsingHeader("Map Tag Component")) {
        //        ImGui::InputText("Map Name", mapName.begin()._Unwrapped(),50);
        //    }
        //};
    };

class ColliderComponent : public Component {
    public:

        sf::FloatRect border;
        bool isTrigger, enabled;
        ColliderComponent(sf::Vector2f position = sf::Vector2f(), sf::Vector2f size = sf::Vector2f(2, 2)) {
            border = sf::FloatRect(position - (size / 2.0f), size);
            isTrigger = false;
            enabled = true;
            componentName = "Collider";
        }

        void draw() {
            if (ImGui::CollapsingHeader("Collider Component")) {
                ImGui::Indent();
                ImGui::Text("Collider Dimensions:");
                ImGui::InputFloat("X##width", &border.width);
                ImGui::InputFloat("Y##height", &border.height);

                ImGui::Text("Collider Position:");
                ImGui::InputFloat("X##left", &border.left);
                ImGui::InputFloat("Y##top", &border.top);

                ImGui::Checkbox("Is Trigger", &isTrigger);
                ImGui::Checkbox("Enabled##Collider", &enabled);
                ImGui::Unindent();
            }
        }
};