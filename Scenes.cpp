#include "Scenes.h"

/**
* Scene2D
*/
Scene2D::Scene2D(){
	if (!this->canvas.create(WINDOW_WIDTH, WINDOW_HEIGHT)) {
		std::cout << "Couldn't Create Scene2D canvas" << std::endl;
	}
	renderSystem=RenderSystem2D(this->canvas);
	entities.push_back(std::make_shared<Entity2D>(&registry,sf::Vector2f(400,400)));
	this->onCreate();
}
void Scene2D::onCreate() {
	std::cout << "OnCreate Method" << std::endl;
	/**
	* Additional Code Here
	*/
}
void Scene2D::onUpdate(float deltaTime) {
	scriptSystem.OnUpdate(deltaTime,registry);
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
	std::cout << "OnDestroy Method" << std::endl;
}
Scene2D::~Scene2D() {
	this->onDestroy();
}
///////////////////////////////////////