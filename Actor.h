#pragma once
/**
* The Actor class will be used to implement scriptiable behaviour for entities.
* Similar to the MonoBehaviour class in unity and Agent class in Unreal, the actor class
* has lifecycle methods that will get called withing the Scene lifecycle methods.
*/


class Actor {
public:
    Actor() {OnCreate();}
    virtual void OnCreate() {};
    virtual void OnUpdate(float deltaTime) = 0;
    virtual void OnRender() = 0;
    virtual void OnFixedUpdate(float fixedDeltaTime) = 0;
    virtual void OnDestroy() = 0;
};