#include "Scene.h"
#include "Log.h"
#include <string>
#include <unordered_map>
class Game {
public:
	Game();
	Game(std::string gameName);
	void addScene(std::string name,std::unique_ptr<Scene> scene);
	void setCurrentScene(std::string);
	void removeScene(std::string name);
	void run();

private:
	std::unordered_map<std::string, std::unique_ptr<Scene>> sceneList;
	std::string currentScene;
	sf::Clock clock;
	sf::Time deltaTime,fixedDeltaTime,cumulatedTime;
	sf::RenderWindow window;

	std::string gameName;
	sf::Image icon;
	bool running=false;
	//Call update every frame and and run update then check if you can run fixed update
	void update();
	void render();
};