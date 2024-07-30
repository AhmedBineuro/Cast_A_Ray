#pragma once
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
extern bool switchScenes(std::string sceneName);
/**
* @struct
* @brief A struct containing the name, type, URL and any flags for the resource.
* The struct keeps 3 strings that contain all the information that will be used to load and store the resource
* @note This will be used internally by the resource manager
*/
struct ResourceLoadingInfo {
    std::string name;
    std::string type;
    std::string URL;
};