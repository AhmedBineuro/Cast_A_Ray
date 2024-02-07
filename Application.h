#include "Scene.h"
#include "Log.h"
#include "Config.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include <string>
#include <unordered_map>
class Application {
public:
	Application();
	Application(std::string gameName);
	
	void addScene(std::string name,Scene* scene);
	void removeScene(std::string name);
	
	bool setCurrentScene(std::string); //Returns true when the sceneName maps to a valid scene
	void setFixedDeltaTime(float fixedDeltaTime);
	void setWindowIcon(std::string icon);
	void setWindowIcon(sf::Image URL);
	
	float getFixedDeltaTime();
	float getDeltaTime();
	
	void run();

private:
	std::unordered_map<std::string, Scene*> sceneList;
	std::string currentScene = "";
	sf::Clock clock;
	sf::Time deltaTime,fixedDeltaTime,cumulatedTime;
	sf::RenderWindow window;
	Settings settings;

	std::string appName;
	sf::Image icon;
	bool running=false,showSettings=false,keybindPressed=false;
	float FPS;
	//Call update every frame and and run update then check if you can run fixed update
	void update();
	void render();
	void renderSettings(float &fixedDeltaTimeGUI, Config& config);//The parameters are for the GUI and settings updates
	void restartWindow();
	//For ImGui
	const char* antiAlias_labels[5] = { "0","2","4","8","15" };
	const int antiAlias_values[5] = { 0,2,4,8,15 };
	int currentAntiAlias = 0;
	bool showFPS;
};