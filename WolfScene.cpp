#include "WolfScene.h"
WolfScene::WolfScene():Scene2D(){
	this->player = new Player(&this->registry, sf::Vector2f(3, 5));
	playercontroller = this->player->getComponent<PlayerController>();
	this->player->camera->linkRenderTarget(&this->canvas);
	cameraRenderSystem=CameraRenderSystem();
	this->mapList.resize(0);
	this->onCreate();
}
WolfScene::WolfScene(std::vector<std::string>mapNames):Scene2D() {
	this->mapList.resize(0);
	this->player = new Player(&this->registry, sf::Vector2f(3,5));
	playercontroller = this->player->getComponent<PlayerController>();
	this->player->camera->linkRenderTarget(&this->canvas);
	cameraRenderSystem = CameraRenderSystem();
	for (auto &name : mapNames) {
		mapList.push_back(Map(name));
	}
	cameraRenderSystem.setMapList(this->mapList);
	this->onCreate();
}
void WolfScene::onCreate() {
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
void WolfScene::onUpdate(float deltaTime) {
	Config& config = Config::getConfig();
	sf::Vector2u window = config.getDimensions();
	if (canvas.getSize() != window) {
		std::cout << "Old Dimensions: " << canvas.getSize().x << " , " << canvas.getSize().y << std::endl;
		std::cout << "New Dimensions: " << window.x << " , " << window.y << std::endl;
		this->canvas.create(window.x, window.y);
		this->renderSystem.setTarget(&this->canvas);
	}
	scriptSystem.OnUpdate(deltaTime, registry);
	/**
	* Additional Code Here
	*/
}
void WolfScene::onFixedUpdate(float fixedDeltaTime) {
	scriptSystem.OnFixedUpdate(fixedDeltaTime, registry);
	/**
	* Additional Code Here
	*/
}
sf::Sprite WolfScene::onRender() {
	Config& config = Config::getConfig();
	Settings settings = config.getSettings();
	canvas.clear();
	cameraRenderSystem.update(registry);
	scriptSystem.OnRender(registry);
	//renderSystem.update(registry);
	canvasSprite.setTexture(canvas.getTexture());
	/**
	* Additional Code Here
	*/

	return canvasSprite;
}
void WolfScene::onDestroy() {
	/**
	* Additional Code Here
	 */
}
// @ TODO Basically the maps don't bind and I want to switch 
// from using an unordered map in the system, to using a reference to 
// the vector of maps
void WolfScene::changeMap(std::string mapName) {
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
void WolfScene::renderDebug() {
}
WolfScene::~WolfScene() {
	delete(this->player);
	this->onDestroy();
}