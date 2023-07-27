#include "Resource_Manager.h"
Resource_Manager Resource_Manager::singleton;
Resource_Manager::Resource_Manager() {
}
Resource_Manager& Resource_Manager::getResourceManager() {
	return singleton;
}

sf::Texture& Resource_Manager::getTexture(std::string name) {
	return *(this->textureMap.at(name).texture);
}
sf::Music &Resource_Manager::getMusic(std::string name) {
	return *(musicMap.at(name).music);
}
sf::Sound Resource_Manager::getSound(std::string name) {
	return *(this->soundMap.at(name).sound);
}

void Resource_Manager::processResourceList(std::string mapName,std::vector<ResourceLoadingInfo> resourceList) {
	for (ResourceLoadingInfo currentResource : resourceList) {
		if(currentResource.type=="texture")
		{
				this->textureMap[currentResource.name] = Texture_Container();
				if (!this->textureMap[currentResource.name].texture->loadFromFile(currentResource.URL)) {
					std::cout << "Failed to load resource: " << currentResource.name << " type:" << currentResource.type << std::endl;
				}
		}
		else if(currentResource.type == "sound")
		{
				this->soundMap[currentResource.name] = Sound_Container();
				if (!this->soundMap[currentResource.name].buffer.loadFromFile(currentResource.URL)) {
					std::cout << "Failed to load resource: " << currentResource.name << " type:" << currentResource.type << std::endl;
				}
				else {
					this->soundMap[currentResource.name].sound->setBuffer(this->soundMap[currentResource.name].buffer);
				}
		}
		else if (currentResource.type == "music")
		{
				this->musicMap[currentResource.name]= Music_Container();
				if (!this->musicMap[currentResource.name].music->openFromFile(currentResource.URL)) {
					std::cout << "Failed to load resource: " << currentResource.name << " type:" << currentResource.type << std::endl;
				}
		}
	}
}