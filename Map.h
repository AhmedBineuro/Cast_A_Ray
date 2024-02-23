#pragma once
#include <vector>
#include <string>
//This class will be the container to all the map information
//This class will not act on any object instead it will just work on the tiles defined inside
class Map {
public:
	Map();
private:
	std::string name;
	std::vector<int> walls;
	std::vector<int> floors;
	std::vector<int> ceilings;
};