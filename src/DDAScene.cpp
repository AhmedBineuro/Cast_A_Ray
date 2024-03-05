#include "DDAScene.h"
DDAScene::DDAScene():Scene2D(){
	this->player = std::make_shared<Player>(&this->registry, sf::Vector2f(3, 5));
	this->entities.push_back(player);
	playercontroller = this->player->getComponent<PlayerController>();
	this->player->camera->linkRenderTarget(&this->canvas);
	this->mapList.resize(0);
	this->onCreate();
}
DDAScene::DDAScene(std::vector<std::string>mapNames):Scene2D() {
	this->mapList.resize(0);
	this->player = std::make_shared<Player>(&this->registry, sf::Vector2f(3, 5));
	this->entities.push_back(player);
	playercontroller = this->player->getComponent<PlayerController>();
	this->player->camera->linkRenderTarget(&this->canvas);
	for (auto &name : mapNames) {
		mapList.push_back(Map(name));
	}
	this->onCreate();
}
void DDAScene::onCreate() {
	/**
	* Additional Code Here
	*/
	if (mapList.size() <= 0)
		return;
	currentMap = 0;
	MapTagComponent tag;
	tag.mapName = mapList[currentMap].getMapName();
	this->player->addComponent(tag);
	this->player->camera->addComponent(tag);
}
void DDAScene::onUpdate(float deltaTime) {
	Config& config = Config::getConfig();
	sf::Vector2u window = config.getDimensions();
	if (canvas.getSize() != window) {
		std::cout << "Old Dimensions: " << canvas.getSize().x << " , " << canvas.getSize().y << std::endl;
		std::cout << "New Dimensions: " << window.x << " , " << window.y << std::endl;
		this->canvas.create(window.x, window.y);
	}
	Systems::EntityScriptSystem::OnUpdate(deltaTime, registry);
	Systems::WolfCollisionSystem(registry,mapList);
	/**
	* Additional Code Here
	*/
}
void DDAScene::onFixedUpdate(float fixedDeltaTime) {
	Systems::EntityScriptSystem::OnFixedUpdate(fixedDeltaTime, registry);

	/**
	* Additional Code Here
	*/
}
sf::Sprite DDAScene::onRender() {
	Config& config = Config::getConfig();
	Settings settings = config.getSettings();
	canvas.clear();
	Systems::DDARenderSystem(registry, mapList);
	Systems::EntityScriptSystem::OnRender(registry);
	Systems::RenderSystem2D(registry,canvas);
	canvasSprite.setTexture(canvas.getTexture());
	/**
	* Additional Code Here
	*/

	return canvasSprite;
}
void DDAScene::onDestroy() {
	/**
	* Additional Code Here
	 */
}
// @ TODO Basically the maps don't bind and I want to switch 
// from using an unordered map in the system, to using a reference to 
// the vector of maps
void DDAScene::changeMap(std::string mapName) {
	int i = 0;
	for (auto& map : this->mapList) {
		if (map.getMapName() == mapName)
			break;
		i++;
	}
	if (i >= this->mapList.size()) {
		return;
	}
	MapTagComponent newTag;
	newTag.mapName = mapName;
	if(this->player->hasComponent< MapTagComponent>())
		this->player->replaceComponent<MapTagComponent>(newTag);
	else this->player->addComponent(newTag);
	if (this->player->camera->hasComponent< MapTagComponent>())
		this->player->camera->replaceComponent<MapTagComponent>(newTag);
	else this->player->camera->addComponent(newTag);
	currentMap = i;
}
void DDAScene::renderDebug() {
	ImGui::Begin("Player settings");
	ImGui::End();
}