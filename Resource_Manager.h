#pragma once
/**
* @todo Rewrite the whole cpp file again :(
*/
#include "Core.h"
#include <vector>
#include <iostream>
#include <map>
#include <unordered_map>
struct Texture_Container {
	std::shared_ptr <sf::Texture> texture;
};
struct Sound_Container {
	sf::SoundBuffer buffer;
	std::shared_ptr <sf::Sound> sound;
};
struct Music_Container {
	std::shared_ptr<sf::Music> music;
};
class Resource_Manager {

public:
	/**
	* @brief Function to access the singleton instance of the resource manager
	*/
	Resource_Manager& getResourceManager();
	
	/**
	* @brief Function to get a texture resource using it's name
	* @param name the name of the resource
	* @returns a reference to the texture object
	* @throws std::out_of_range
	*/
	sf::Texture& getTexture(std::string name);
	/**
	* @brief Function to get a music resource using it's name
	* @param name the name of the resource
	* @returns a reference to the music object
	* @throws std::out_of_range
	*/
	sf::Music& getMusic(std::string name);
	/**
	* @brief Function to get a sound resource using it's name
	* @param name the name of the resource
	* @returns a copy to the sound object
	* @throws std::out_of_range
	*/
	sf::Sound getSound(std::string name);
	/**
	* @brief Function to process a resource list for a given map
	* The function will load all the unloaded resources and save the dependencies for the map
	* @param mapName the name of the map/level
	* @param resourceList the list of the resource information 
	*/
	void processResourceList(std::string mapName,std::vector<ResourceLoadingInfo> resourceList);

private:
	/*Resource maps*/
	std::map<std::string, Texture_Container> m_textureMap;
	std::map<std::string, Sound_Container> m_soundMap;
	std::map<std::string, Music_Container> m_musicMap;
	// Private constructor for singleton instance
	Resource_Manager();
	// Private copy constructor and assignment operator to prevent copy
	Resource_Manager(const Resource_Manager&) = delete;
	static Resource_Manager m_singleton;
	Resource_Manager& operator=(const Resource_Manager&) = delete;
};