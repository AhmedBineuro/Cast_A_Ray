#include "Application.h"
Application::Application() {
	this->gameName = "Cast-A-Ray Application";
	this->window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), this->gameName);
	fixedDeltaTime = sf::Time(sf::seconds(1.0f / 60.0f));
	if (!icon.loadFromFile("./casta.png"))
		std::cout << "Failed to load window icon" << std::endl;
	else
		window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	FPS = 0;
}
Application::Application(std::string gameName) {
	this->gameName = gameName;
	this->window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), this->gameName);
	fixedDeltaTime = sf::Time(sf::seconds(1.0f / 60.0f));
	if (!icon.loadFromFile("./casta.png"))
		std::cout << "Failed to load window icon" << std::endl;
	else
		window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	FPS = 0;
}
void Application::addScene(std::string name, Scene* scene) {
	if (currentScene == "")
		currentScene = name;
	sceneList[name] = scene;
}

void Application::setCurrentScene(std::string name)
{
	if (sceneList.find(name) != sceneList.end()) {
		currentScene = name;
	}
}
void Application::removeScene(std::string name) {
	if (sceneList.find(name) != sceneList.end()) {
		sceneList.erase(name);
	}
}

void Application::setFixedDeltaTime(float fixedDeltaTime) {
	this->fixedDeltaTime = sf::seconds(fixedDeltaTime);
}

void Application::setWindowIcon(std::string URL) {
	sf::Image ico;
	if (!ico.loadFromFile(URL))
		std::cout << "Failed to load window icon" << std::endl;
	else
	{
		icon = ico;
		window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	}
}

void Application::setWindowIcon(sf::Image icon) {
	this->icon = icon;
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

float Application::getFixedDeltaTime() {
	return fixedDeltaTime.asSeconds();
}

float Application::getDeltaTime() {
	return deltaTime.asSeconds();
}

void Application::run() {
	running = true;
	while (running) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
			{
				window.close();
				running = false;
			}
		}
		update();
		render();
		//std::cout << "FPS: " << FPS << std::endl;
	}
	window.close();
}
void Application::render() {
	window.clear();
	if (sceneList.find(currentScene) != sceneList.end())
		window.draw(sceneList[currentScene]->onRender());
	window.display();
}

void Application::update() {
	deltaTime = clock.restart();
	globalDeltaTime = deltaTime.asSeconds();
	FPS = 1.0f / deltaTime.asSeconds();
	cumulatedTime += deltaTime;
	while (cumulatedTime >= fixedDeltaTime){
		cumulatedTime -= fixedDeltaTime;
		if (sceneList.find(currentScene) != sceneList.end())
			sceneList[currentScene]->onFixedUpdate(fixedDeltaTime.asSeconds());
	}
	if (sceneList.find(currentScene) != sceneList.end())
		sceneList[currentScene]->onUpdate(deltaTime.asSeconds());
}