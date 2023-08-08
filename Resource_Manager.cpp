#include "Resource_Manager.h"
Resource_Manager Resource_Manager::m_singleton;
Resource_Manager::Resource_Manager() {
	std::shared_ptr<sf::Texture> defaultTexture = std::make_shared<sf::Texture>();
	if (!defaultTexture->loadFromFile("no_text.png")) {
		throw std::runtime_error("Failed to load default texture.");
	}
	std::shared_ptr<sf::Font> defaultFont = std::make_shared<sf::Font>();
	if (!defaultFont->loadFromFile("./CourierPrime-Regular.ttf")) {
		throw std::runtime_error("Failed to load default texture.");
	}
	// Store the default texture in the textureMap with a key like "default" or "default_texture".
	this->fontMap["DEF_LOG"] = Font_Container{ defaultFont};
}
Resource_Manager& Resource_Manager::getResourceManager() {
	static Resource_Manager m_singleton;
	return m_singleton;
}

sf::Texture& Resource_Manager::getTexture(std::string name) {
	if(this->textureMap.find(name) !=this->textureMap.end())
		return *(this->textureMap.at(name).texture);
	else {
		return *(this->textureMap.at("NO_TEXT").texture);
	}
}
sf::Music &Resource_Manager::getMusic(std::string name) {
	
	auto result = this->musicMap.find(name);
	if (result != this->musicMap.end())
		return *(musicMap.at(name).music);
	else
		throw std::runtime_error("Failed to locate music file.");
}
sf::Sound& Resource_Manager::getSound(std::string name) {
	
	if (this->soundMap.find(name) != this->soundMap.end())
		return *(soundMap.at(name).sound);
	else
		throw std::runtime_error("Failed to locate sound file.");
}

sf::Font& Resource_Manager::getFont(std::string name) {

	if (this->fontMap.find(name) != this->fontMap.end())
		return *(fontMap.at(name).font);
	else
		throw* (fontMap.at("DEF_LOG").font);
}

void Resource_Manager::processResourceList(std::string mapName,std::vector<ResourceLoadingInfo> resourceList) {
	for (ResourceLoadingInfo currentResource : resourceList) {
		if(currentResource.type=="texture")
		{
				this->textureMap[currentResource.name] = Texture_Container();
				this->textureMap[currentResource.name].texture = std::make_shared<sf::Texture>();
				if (!this->textureMap[currentResource.name].texture->loadFromFile(currentResource.URL)) {
					std::cout << "Failed to load resource: " << currentResource.name << " type:" << currentResource.type << std::endl;
				}
		}
		else if(currentResource.type == "sound")
		{
				this->soundMap[currentResource.name] = Sound_Container();
				this->soundMap[currentResource.name].sound = std::make_shared<sf::Sound>();
				if (!this->soundMap[currentResource.name].buffer.loadFromFile(currentResource.URL)) {
					std::cout << "Failed to load resource: " << currentResource.name << " type:" << currentResource.type << std::endl;
				}
				else {
					this->soundMap[currentResource.name].sound->setBuffer(this->soundMap[currentResource.name].buffer);
				}
		}
		else if (currentResource.type == "music")
		{
			this->musicMap[currentResource.name].music = std::make_shared<sf::Music>();
				this->musicMap[currentResource.name]= Music_Container();
				if (!this->musicMap[currentResource.name].music->openFromFile(currentResource.URL)) {
					std::cout << "Failed to load resource: " << currentResource.name << " type:" << currentResource.type << std::endl;
				}
		}
	}
}