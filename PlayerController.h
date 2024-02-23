#pragma once
#include "Core.h"
#include "Actor.h"
#include "CoreComponents.h"
#define AVAILABLE_KEYS 7

//Add more controls into the enum
enum Keybinds
{
    FORWARDS,
    BACKWARDS,
    LEFT,
    RIGHT,
    LOOK_RIGHT,
    LOOK_LEFT,
    SPRINT
};

class PlayerController :public Actor {
public:
    PlayerController();
    PlayerController(TransformComponent* playerTransform, SpriteComponent* playerSprite, ControllableComponet* controllableComponent);
    void OnCreate();
    void OnUpdate(float deltaTime);
    void OnRender();
    void OnFixedUpdate(float fixedDeltaTime);
    void OnDestroy();
    
    void setKeyBind(Keybinds key, sf::Keyboard::Key key_code);
    void setSensitivity(float sensitivity);
    void setPlayer(TransformComponent* playerTransform, SpriteComponent* playerSprite, ControllableComponet* controllableComponent);
    void setMovementMultiplier(float movementMultiplier);

    float getSensitivity();
protected:
    TransformComponent* playerTransform; // This what the script will manipulate
    SpriteComponent* playerSprite; // This what the script will manipulate
    ControllableComponet* controllableComponent;
    //MODIFY THIS TO INCLUDE NEW CONTROLS
    sf::Keyboard::Key keyBinds[AVAILABLE_KEYS] = {
        sf::Keyboard::W,
        sf::Keyboard::S,
        sf::Keyboard::A,
        sf::Keyboard::D,
        sf::Keyboard::Right,
        sf::Keyboard::Left,
        sf::Keyboard::LShift
    };
};