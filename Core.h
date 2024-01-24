#pragma once
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
extern float globalDeltaTime;
extern void switchScenes(std::string sceneName);
/**
* @struct
* @brief A struct containing the floor, wall, and ceiling values for a given tile.
* The struct keeps 3 ints representing the tile index. Each value will be used to look up the corresponding texture/ color for the given tile.
* @note This will be used internally by the map class
*/
struct TileId {
    int wall;
    int floor;
    int ceiling;
};
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