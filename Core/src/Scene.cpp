#include "Core\include\Scene.h"
entt::entity Scene::addEntity() {
	std::shared_ptr<Entity> newEnt = std::make_shared<Entity>(&this->registry);
	this->entities.push_back((newEnt));
	newEnt->setName("Entity " + std::to_string(entity_counter));
	entity_counter++;
	return newEnt->getHandle();
	
}
void Scene::removeEntity(entt::entity entity) {
	int i = 0;
	for (auto ent : this->entities) {
		if (ent->getHandle() == entity)
			break;
		i++;
	}
	if (i == this->entities.size())
		return;
	this->entities.erase(this->entities.begin() + i);
}
void Scene::createCanvas(std::string name, int width, int height) {
	this->canvasMap[name] = std::make_shared<sf::RenderTexture>();
	this->canvasMap[name]->create(width, height);
}
void Scene::deleteCanvas(std::string name) {
	canvasMap.erase(name);
	if (name == this->currentCanvas) this->currentCanvas = "";
}
std::unordered_map<std::string, std::shared_ptr<sf::RenderTexture>>& Scene::getCanvasMap(){
	return canvasMap;
}

std::string&  Scene::getcurrenCanvas() {
	return currentCanvas;
}

std::vector<std::shared_ptr<Entity>>& Scene::getEntityList(){
	return entities;
}





