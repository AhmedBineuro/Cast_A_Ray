#pragma once
class Actor {
public:
    virtual void OnCreate() = 0;
    virtual void OnDestroy() = 0;
    virtual void OnStart() = 0;
    virtual void OnUpdate(float deltaTime) = 0;
    virtual void OnFixedUpdate(float fixedDeltaTime) = 0;
    virtual void OnEnable() = 0;
    virtual void OnDisable() = 0;

    virtual ~Actor() {} // Ensure a virtual destructor for derived classes
};