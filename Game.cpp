#include "Game.h"
Game::Game() {
	this->gameName = "Cast-A-Ray Game";
	this->window.create(sf::VideoMode(800, 800), this->gameName);
	fixedDeltaTime = sf::Time(sf::seconds(1.0f / 60.0f));
	if (!icon.loadFromFile("./casta.png"))
		std::cout << "Failed to load window icon" << std::endl;
	else
		window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}
Game::Game(std::string gameName) {
	this->gameName = gameName;
	this->window.create(sf::VideoMode(800, 800), this->gameName);
	fixedDeltaTime = sf::Time(sf::seconds(1.0f / 60.0f));
	if (!icon.loadFromFile("./casta.png"))
		std::cout << "Failed to load window icon" << std::endl;
	else
		window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}
void Game::addScene(std::string name, std::unique_ptr<Scene> scene) {
	sceneList[name] = std::move(scene);
}

void Game::setCurrentScene(std::string name)
{
	if (sceneList.find(name) != sceneList.end()) {
		currentScene = name;
	}
}
void Game::removeScene(std::string name) {
	if (sceneList.find(name) != sceneList.end()) {
		sceneList.erase(name);
	}
}

void Game::render() {
	window.clear();
	if (sceneList.find(currentScene) != sceneList.end())
		sceneList[currentScene].get()->render();
	window.display();
}

void Game::update() {
	deltaTime = clock.restart();
	cumulatedTime += deltaTime;
	while (cumulatedTime >= fixedDeltaTime){
		cumulatedTime -= fixedDeltaTime;
		if (sceneList.find(currentScene) != sceneList.end())
			sceneList[currentScene].get()->onFixedUpdate(fixedDeltaTime.asSeconds());
	}
	if (sceneList.find(currentScene) != sceneList.end())
		sceneList[currentScene].get()->onUpdate(deltaTime.asSeconds());
}

void Game::run() {
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
	}
	window.close();
}