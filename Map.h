#pragma once
#include <vector>
#include <string>
#include <filesystem>
#include <iostream>
#include <fstream>
#include "Core.h"
#include "nlohmann/json.hpp"
#include <unordered_map>
#include "Resource_Manager.h"

//This class will be the container to all the map information
//This class will not act on any object instead it will just work on the tiles defined inside
/*
* You should theoretically think about each tile 
* in the grid to be 1x1 pixels. The tileSprite is purely for visualization
*/
class Map {
public:
	Map();
	Map(std::string name);

	void setMap(std::string name);
	void refreshMap();
	void draw(sf::RenderTarget& renderTarget, sf::Vector2f topleftPosition=sf::Vector2f(0,0));
	std::string getMapName();
	std::vector<std::vector<int>> walls;
	std::vector<std::vector<int>> floors;
	std::vector<std::vector<int>> ceilings;
	std::unordered_map<int, std::string> wallMapping;
	std::unordered_map<int, std::string> floorMapping;
	std::unordered_map<int, std::string> ceilingMapping;
	std::vector<int> ignoreRaycast;
	std::vector<int> ignoreCollision;
	sf::RectangleShape tileSprite;
private:
	void loadResources();
	std::string normalizePathSlashes(const std::string path);
	void processMapFile();
	std::string name;
};