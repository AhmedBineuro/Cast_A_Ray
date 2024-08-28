#pragma once
#include "Core\include\Core.h"
#include "Engine\include\Actor.h"
#include "Core\include\Entity.h"
#define AVAILABLE_KEYS 11
//Add more controls into the enum
enum Keybinds
{
    FORWARDS,
    BACKWARDS,
    LEFT,
    RIGHT,
    UP,
    DOWN,
    LOOK_RIGHT,
    LOOK_LEFT,
    LOOK_UP,
    LOOK_DOWN,
    SPRINT
};

class PlayerController :public Actor {
public:
    PlayerController();
    PlayerController(Entity* player, Entity* camera);
    void OnCreate();
    void OnUpdate(float deltaTime);
    void OnRender();
    void OnFixedUpdate(float fixedDeltaTime);
    void OnDestroy();
    virtual void OnEventLoop(sf::Event event) override;

    void setKeyBind(Keybinds key, sf::Keyboard::Key key_code);
    void setPlayer(Entity* player, std::shared_ptr<Entity> camera);
    void setPlayer(std::shared_ptr<Entity>);
    void setCamera(std::shared_ptr<Entity>);
    virtual void renderImGui() override;
protected:
    std::weak_ptr<Entity> player;
    std::weak_ptr<Entity> camera;
    sf::Vector2i previousMousePosition;
    bool keyStates[AVAILABLE_KEYS] = {false};
    //MODIFY THIS TO INCLUDE NEW CONTROLS
    sf::Keyboard::Key keyBinds[AVAILABLE_KEYS] = {
        sf::Keyboard::W,
        sf::Keyboard::S,
        sf::Keyboard::A,
        sf::Keyboard::D,
        sf::Keyboard::Space,
        sf::Keyboard::LControl,
        sf::Keyboard::Right,
        sf::Keyboard::Left,
        sf::Keyboard::Up,
        sf::Keyboard::Down,
        sf::Keyboard::LShift
    };
};