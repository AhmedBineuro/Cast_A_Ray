#include "Scene.h"
#include "Log.h"
#include <string>
#include <unordered_map>
class Application {
public:
	Application();
	Application(std::string gameName);
	
	void addScene(std::string name,Scene* scene);
	void removeScene(std::string name);
	
	void setCurrentScene(std::string);
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

	std::string appName;
	sf::Image icon;
	bool running=false;
	float FPS;
	//Call update every frame and and run update then check if you can run fixed update
	void update();
	void render();
};