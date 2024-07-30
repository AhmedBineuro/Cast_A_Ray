#pragma once
#include <string>
class Component {
public:
    virtual void draw() {};
    std::string componentName;
};