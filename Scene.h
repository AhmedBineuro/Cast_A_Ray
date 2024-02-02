#pragma once
#include "Resource_Manager.h"
#include "Map_Reader.h"
#include "entt.hpp"
#include "System.h"

/*
 * @brief This template Scene class will provide all the methods that will be called by the Game class
*/
class Scene {
public:
    // Lifecycle methods
    virtual void onCreate()=0;
    virtual void onUpdate(float deltaTime)=0;
    virtual void onFixedUpdate(float fixedDeltaTime)=0;
    //Should return the canvas result as a sprite and is called every render call
    virtual sf::Sprite onRender()=0;
    virtual void onDestroy()=0;
protected:
    sf::RenderTexture canvas;
    sf::Sprite canvasSprite;
};