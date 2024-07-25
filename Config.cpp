#include "Config.h"
Config Config::config;
Config::Config() {
	nlohmann::json data;
	std::ifstream configFile("./Config.json");
	settings.requiresRestart = false;
	nlohmann::json parsedSettings;
	if (configFile.is_open()) {
		configFile >> parsedSettings;
		configFile.close();
		parsedSettings = parsedSettings["Config"];
		settings.fullscreen = parsedSettings["fullscreen"];
		settings.capFrameRate = parsedSettings["capFrameRate"];
		settings.vsync = parsedSettings["vsync"];
		settings.width = parsedSettings["windowDimensions"][0];
		settings.height = parsedSettings["windowDimensions"][1];
		settings.maxFrameRate = parsedSettings["maxFrameRate"];
		fixedDeltaTime = parsedSettings["fixedDeltaTime"];
		settings.antiAliasingLevel = parsedSettings["antiAliasingLevel"];
		settings.videoSettings.antialiasingLevel = parsedSettings["antiAliasingLevel"];
		settings.renderResolution.x = parsedSettings["renderResolution"][0];
		settings.renderResolution.y = parsedSettings["renderResolution"][1];
	}
	else {
		std::cout << "Error getting config file" << std::endl;
		settings.fullscreen = false;
		settings.capFrameRate = false;
		settings.vsync = false;
		settings.width = 800;
		settings.height = 800;
		settings.antiAliasingLevel = 4;
		settings.maxFrameRate = 60;
		fixedDeltaTime = 0.3f;
		settings.videoSettings.antialiasingLevel = 4;
		settings.renderResolution = sf::Vector2u(400,400);
	}
	deltaTime = 0.0f;
	
}
Config& Config::getConfig() {
	static Config config;
	return config;
};

void Config::setCurrentScene(std::string sceneName) {
	if (switchScenes(sceneName))
		currentScene = sceneName;
}
std::string Config::getCurrentScene() {
	return currentScene;
}
void Config::setDeltaTime(float deltaTime) {
	this->deltaTime = deltaTime;
}
void Config::setFixedDeltaTime(float fixedDeltaTime) {
	this->fixedDeltaTime = fixedDeltaTime;
}
void Config::setSettings(Settings newSettings) {
	bool antialiasCheck = newSettings.antiAliasingLevel != settings.antiAliasingLevel;
	bool fullscreenCheck = newSettings.fullscreen != settings.fullscreen;
	if (antialiasCheck || fullscreenCheck)
		newSettings.requiresRestart = true;
	settings=newSettings;
	settings.videoSettings.antialiasingLevel = settings.antiAliasingLevel;
}
void Config::setDimensions(int width, int height) {
	settings.width = width;
	settings.height = height;
}
void Config::setRenderResolution(int width, int height)
{
	settings.renderResolution.x = width;
	settings.renderResolution.y = height;
}
void Config::setRestartRequiredFlag(bool value) {
	settings.requiresRestart = value;
}


Settings Config::getSettings() {
	return settings;
}
float Config::getFixedDeltaTime() {
	return fixedDeltaTime;
}
float Config::getDeltaTime() {
	return deltaTime;
}
sf::Vector2u Config::getDimensions(){
	return sf::Vector2u(settings.width, settings.height);
}

sf::Vector2u Config::getRenderResolution() {
	return settings.renderResolution;
}
bool Config::isFrameRateCapped(){
	return settings.capFrameRate;
}
bool Config::isVysnc(){
	return settings.vsync;
}
bool Config::RestartRequired() {
	return settings.requiresRestart;
}
int Config::getMaxFrameRate() {
	return settings.maxFrameRate;
}



bool Config::applyChanges() {
	std::ofstream file("./Config.json");
	if (file.is_open()) {
		nlohmann::json newSettings;
		newSettings["Config"];
		newSettings["Config"]["fullscreen"] = settings.fullscreen;
		newSettings["Config"]["capFrameRate"] = settings.capFrameRate;
		newSettings["Config"]["vsync"] = settings.vsync;
		newSettings["Config"]["windowDimensions"] = { settings.width,settings.height };
		newSettings["Config"]["maxFrameRate"] = settings.maxFrameRate;
		newSettings["Config"]["antiAliasingLevel"] = settings.antiAliasingLevel;
		newSettings["Config"]["fixedDeltaTime"] = fixedDeltaTime;
		newSettings["Config"]["renderResolution"] = {settings.renderResolution.x,settings.renderResolution.y};
		file << newSettings.dump();
		file.close();
	}
	return settings.requiresRestart;
}