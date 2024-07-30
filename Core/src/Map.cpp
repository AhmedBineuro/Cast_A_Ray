#include "Core\include\Map.h"

Map::Map() {
	this->floors.resize(0);
	this->walls.resize(0);
	this->ceilings.resize(0);
	this->ignoreCollision.resize(0);
	this->ignoreRaycast.resize(0);
	tileSprite = sf::RectangleShape(sf::Vector2f(50,50));
	this->name = "";
}
Map::Map(std::string name) {
	this->floors.resize(0);
	this->walls.resize(0);
	this->ceilings.resize(0);
	this->ignoreCollision.resize(0);
	this->ignoreRaycast.resize(0);
	tileSprite = sf::RectangleShape(sf::Vector2f(50, 50));
	this->name = name;
	loadResources();
}

void Map::setMap(std::string name) {
	this->name = name;
	processMapFile();
}
void Map::refreshMap() {
	processMapFile();
}
void Map::draw(sf::RenderTarget& renderTarget,sf::Vector2f topleftPosition) {
	Resource_Manager& rm = Resource_Manager::getResourceManager();
	for (int i = 0; i < walls.size(); i++) {
		for (int j = 0; j < walls[i].size(); j++) {
			std::string textureName;
			bool floor = false;
			//If it is not in the ignore list, draw it as a floor tile
			if (std::find(this->ignoreRaycast.begin(), this->ignoreRaycast.end(), walls[i][j]) != this->ignoreRaycast.end()) 
			{
				floor = true;
				textureName = this->floorMapping[floors[i][j]];
			}
			else {
				textureName= this->wallMapping[walls[i][j]];
			}
			rm.getTexture(textureName).setRepeated(true);
			tileSprite.setTexture(&(rm.getTexture(textureName)));
			if (floor) tileSprite.setFillColor(sf::Color(150, 150, 150));
			else tileSprite.setFillColor(sf::Color(255, 255, 255));
			tileSprite.setPosition(topleftPosition.x+(j*tileSprite.getSize().x), topleftPosition.y + (i * tileSprite.getSize().y));

			renderTarget.draw(tileSprite);
		}
	}
}
std::string Map::getMapName() {
	return this->name;
}


/*
* @TODO Have to change this to allow for multiple maps to share same resource files
*/
void Map::loadResources() {
	if (name == "")
		return;
	std::string path = "./"+this->name;
	std::vector<ResourceLoadingInfo> rlis(0);
	namespace fs=std::filesystem;
	try {
		if (fs::exists(path) && fs::is_directory(path))
		{
			for (const auto& entry : fs::directory_iterator(path)) {	
				//If we face a directory try and load the resources inside it
				if (fs::is_directory(entry.status())) {
					std::string type = entry.path().filename().stem().string();
					if (type != "music"&& type.size()>0) {
						type.erase(type.end()-1);
					}
					for (const auto& resource : fs::directory_iterator(entry.path()))
					{
						std::string name = resource.path().filename().stem().string();
						std::string URL = normalizePathSlashes(resource.path().string());
						rlis.push_back({ name, type, URL});
					}
				} // If we face the layout file process that
				else if (entry.path().filename() == "layout.car") {
					processMapFile();
				}
			}
		}
	}
	catch (const fs::filesystem_error& err) {
		std::cerr << "Filesystem error: " << err.what() << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << "General error: " << e.what() << std::endl;
	}
	Resource_Manager& rm = Resource_Manager::getResourceManager();
	rm.processResourceList(this->name, rlis);
}
std::string Map::normalizePathSlashes(const std::string path) {
	std::string normalizedPath = path;
	std::replace(normalizedPath.begin(), normalizedPath.end(), '\\', '/');
	return normalizedPath;
}

void Map::processMapFile() {
	std::ifstream file("./" + name + "/layout.car");
	nlohmann::json data;
	this->walls.clear();
	this->floors.clear();
	this->ceilings.clear();
	this->wallMapping.clear();
	this->floorMapping.clear();
	this->ceilingMapping.clear();
	this->ignoreRaycast.clear();
	try {
		file >> data;

		nlohmann::json layout = data["layout"];
		for (auto& row : layout["wall"]) {
			std::vector<int> vectorRow = row.get<std::vector<int>>();
			this->walls.push_back(vectorRow);
		}
		for (auto& row : layout["floor"]) {
			std::vector<int> vectorRow = row.get<std::vector<int>>();
			this->floors.push_back(vectorRow);
		}
		for (auto& row : layout["ceiling"]) {
			std::vector<int> vectorRow = row.get<std::vector<int>>();
			this->ceilings.push_back(vectorRow);
		}

		nlohmann::json mappings = data["mapping"];
		for (auto& row : mappings["wall"]) {
			for (auto& [key, value] : row.items()) {
				int integerKey = std::stoi(key);
				this->wallMapping[integerKey] = value;
			}
		}
		for (auto& row : mappings["floor"]) {
			for (auto& [key, value] : row.items()) {
				int integerKey = std::stoi(key);
				this->floorMapping[integerKey] = value;
			}
		}
		for (auto& row : mappings["ceiling"]) {
			for (auto& [key, value] : row.items()) {
				int integerKey = std::stoi(key);
				this->ceilingMapping[integerKey] = value;
			}
		}
		ignoreRaycast = data["ignore raycast"].get<std::vector<int>>();
		ignoreCollision = data["ignore collision"].get<std::vector<int>>();
		transparent = data["transparent"].get<std::vector<int>>(); // TODO USE FOR TRANSPARENCY
	}
	catch (const nlohmann::json::parse_error& e) {
		std::cerr << "Parsing error: " << e.what() << '\n';
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << '\n';
	}
}
