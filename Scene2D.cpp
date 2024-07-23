#include "Scene2D.h"
Scene2D::Scene2D() {
	Config& config = Config::getConfig();
	Settings settings = config.getSettings();
	if (!this->canvas.create(settings.width, settings.height)) {
		std::cout << "Couldn't Create Scene2D canvas" << std::endl;
	}
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
	}
	Systems::EntityScriptSystem::OnUpdate(deltaTime, registry);
	/**
	* Additional Code Here
	*/
}
void Scene2D::onFixedUpdate(float fixedDeltaTime) {
	Systems::EntityScriptSystem::OnFixedUpdate(fixedDeltaTime, registry);
	/**
	* Additional Code Here
	*/
}
sf::Sprite Scene2D::onRender() {
	Config& config = Config::getConfig();
	Settings settings = config.getSettings();
	canvas.clear();
	Systems::EntityScriptSystem::OnRender(registry);
	Systems::RenderSystem2D(registry, canvas);
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

void Scene2D::renderImGui()
{
}

void Scene2D::renderEntitiesImGui()
{
	for (auto entity : this->entities)
	{
		std::string title = entity->getName();
		if (ImGui::CollapsingHeader(title.c_str()))
		{
			ImGui::PushID((unsigned int)entity->getHandle());
			ImGui::Indent();
			entity->drawImGui();
			ImGui::Unindent();
			ImGui::PopID();
		}
	}
}

Entity* Scene2D::createEntity() {
	entities.push_back(std::make_shared<Entity>(&registry));
	return entities[entities.size()-1].get();
}
Scene2D::~Scene2D() {
	this->onDestroy();
}