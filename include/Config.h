#pragma once
#include "Core.h"
#include <fstream>
#include "nlohmann/json.hpp"

struct Settings {
	sf::ContextSettings videoSettings;
	bool fullscreen, capFrameRate, vsync, requiresRestart;
	int width, height, maxFrameRate, antiAliasingLevel;
};
/**The configs class will hold all the application settings 
* and will read and write to a Config.json file. That way
*/
class Config {
public:
	static Config& getConfig();

	void setCurrentScene(std::string);
	std::string getCurrentScene();

	//ONLY FOR USE FOR THE APPLICATION CLASS
	void setDeltaTime(float);
	void setFixedDeltaTime(float);
	void setSettings(Settings);
	void setDimensions(int, int);
	void setRestartRequiredFlag(bool);
	
	Settings getSettings();
	float getFixedDeltaTime();
	float getDeltaTime();
	sf::Vector2u getDimensions();
	bool isFrameRateCapped();
	bool isVysnc();
	bool RestartRequired();
	int getMaxFrameRate();
	/**
	* @brief Function to commits changes to Config.json file
	* The Function commits the changes to the config file and also updates the window
	* @returns bool true if needs a restart and false otherwise
	*/
	bool applyChanges();
private:
	Settings settings;
	float deltaTime,fixedDeltaTime;
	std::string currentScene;
	//Singleton Pattern
	static Config config;
	Config();
	Config(const Config&) = delete;
	Config& operator=(const Config&)=delete;
};