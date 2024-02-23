#include "Scene2D.h"
Scene2D::Scene2D() {
	Config& config = Config::getConfig();
	Settings settings = config.getSettings();
	if (!this->canvas.create(settings.width, settings.height)) {
		std::cout << "Couldn't Create Scene2D canvas" << std::endl;
	}
	renderSystem = RenderSystem2D(this->canvas);
	///////////////////// Player Test
	Resource_Manager& rm = Resource_Manager::getResourceManager();
	ResourceLoadingInfo rli;
	rli.name = "PlayerSprite";
	rli.type = "texture";
	rli.URL = "./Player.png";
	rm.loadResource(rli);
	for (int i = 0; i < 10; i++) {
	Player player(&registry,sf::Vector2f(rand()/(float)RAND_MAX*settings.width/2, rand() / (float)RAND_MAX * settings.height/2));
	player.setSpriteTexture(rm.getTexture("PlayerSprite"));
	}
	///////////////////////
	this->onCreate();
}
void Scene2D::onCreate() {
	/**
	* Additional Code Here
	*/
}
void Scene2D::onUpdate(float deltaTime) {
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
void Scene2D::onFixedUpdate(float fixedDeltaTime) {
	scriptSystem.OnFixedUpdate(fixedDeltaTime, registry);
	/**
	* Additional Code Here
	*/
}
sf::Sprite Scene2D::onRender() {
	Config& config = Config::getConfig();
	Settings settings = config.getSettings();
	canvas.clear();
	scriptSystem.OnRender(registry);
	renderSystem.update(registry);
	canvasSprite.setTexture(canvas.getTexture());
	/**
	* Additional Code Here
	*/

	return canvasSprite;
}
void Scene2D::onDestroy() {
	/**
	* Additional Code Here
	 */
}

Entity* Scene2D::createEntity() {
	entities.push_back(std::make_shared<Entity>(&registry));
	return entities[entities.size()-1].get();
}
Scene2D::~Scene2D() {
	this->onDestroy();
}