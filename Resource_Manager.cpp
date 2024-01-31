#include "Resource_Manager.h"
Resource_Manager Resource_Manager::m_singleton;
Resource_Manager::Resource_Manager() {
	std::shared_ptr<sf::Texture> defaultTexture = std::make_shared<sf::Texture>();
	if (!defaultTexture->loadFromFile("no_text.png")) {
		throw std::runtime_error("Failed to load default texture.");
	}
	this->textureMap["DEF_TEXT"] = Texture_Container{ defaultTexture };
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
		return *(this->textureMap.at("DEF_TEXT").texture);
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

void Resource_Manager::processResourceList(std::string mapName,std::vector<ResourceLoadingInfo> resourceList,  float* progress_percentage) {
	float totalCount = resourceList.size();
	float currentCount = 0;
	*progress_percentage = 0;
	for (ResourceLoadingInfo currentResource : resourceList) {
		loadResource(currentResource);
		currentCount++;
		*progress_percentage = currentCount / totalCount;
	}
}

void Resource_Manager::processResourceList(std::string mapName, std::vector<ResourceLoadingInfo> resourceList) {
	for (ResourceLoadingInfo currentResource : resourceList) {
		loadResource(currentResource);
	}
}
//@todo make this better, use type based lookup
void Resource_Manager::loadResource(ResourceLoadingInfo resourceInfo) {
	if (resourceInfo.type == "texture")
	{
		this->textureMap[resourceInfo.name] = Texture_Container();
		this->textureMap[resourceInfo.name].texture = std::make_shared<sf::Texture>();
		if (!this->textureMap[resourceInfo.name].texture->loadFromFile(resourceInfo.URL)) {
			std::cout << "Failed to load resource: " << resourceInfo.name << " type:" << resourceInfo.type << std::endl;
		}
	}
	else if (resourceInfo.type == "sound")
	{
		this->soundMap[resourceInfo.name] = Sound_Container();
		this->soundMap[resourceInfo.name].sound = std::make_shared<sf::Sound>();
		if (!this->soundMap[resourceInfo.name].buffer.loadFromFile(resourceInfo.URL)) {
			std::cout << "Failed to load resource: " << resourceInfo.name << " type:" << resourceInfo.type << std::endl;
		}
		else {
			this->soundMap[resourceInfo.name].sound->setBuffer(this->soundMap[resourceInfo.name].buffer);
		}
	}
	else if (resourceInfo.type == "music")
	{
		this->musicMap[resourceInfo.name] = Music_Container();
		this->musicMap[resourceInfo.name].music = std::make_shared<sf::Music>();
		if (!this->musicMap[resourceInfo.name].music->openFromFile(resourceInfo.URL)) {
			std::cout << "Failed to load resource: " << resourceInfo.name << " type:" << resourceInfo.type << std::endl;
		}
	}
	else if (resourceInfo.type == "font") {
		this->fontMap[resourceInfo.name] = Font_Container();
		this->fontMap[resourceInfo.name].font = std::make_shared<sf::Font>();
		if (!this->fontMap[resourceInfo.name].font->loadFromFile(resourceInfo.URL)) {
			std::cout << "Failed to load resource: " << resourceInfo.name << " type:" << resourceInfo.type << std::endl;
		}
	}
}