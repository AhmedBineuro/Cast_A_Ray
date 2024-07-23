#pragma once
#ifndef DDA_SCENE_H
#define DDA_SCENE_H
#include "Scene2D.h"
#include "Player.h"

// This is officially the scene for wolfenstien 3D style games!
class DDAScene :public Scene2D {
public:

	DDAScene() :Scene2D() {
		this->player = std::make_shared<Player>(&this->registry, sf::Vector2f(2, 2));
		std::shared_ptr<Camera> cam = std::make_shared<Camera>(&this->registry, sf::Vector2f(2, 2));
		this->entities.push_back(player);
		this->player->setName("Player");
		this->entities.push_back(cam);
		player->setCamera(cam.get());
		this->player->camera->setName("Player Camera");
		this->player->camera->linkRenderTarget(&this->canvas);
		this->map = Map();
		this->onCreate();
	}
	DDAScene(std::string mapName) :Scene2D() {
		this->map = Map(mapName);
		std::shared_ptr<Camera> cam = std::make_shared<Camera>(&this->registry, sf::Vector2f(2, 2));
		this->player = std::make_shared<Player>(&this->registry, sf::Vector2f(2, 2));
		this->entities.push_back(player);
		this->entities.push_back(cam);
		player->setCamera(cam.get());
		
		this->player->camera->linkRenderTarget(&this->canvas);
		this->onCreate();
	}
	virtual void onCreate() override{
		currentMap = 0;
		this->playerTransform = player->getComponent<TransformComponent>();
		this->cameraComponent = this->player->camera->getComponent<CameraComponent>();
		playercontroller = this->player->getComponent<PlayerController>();
		/**
		* Additional Code Here
		*/
	}
	virtual void onUpdate(float deltaTime) override{
		Config& config = Config::getConfig();
		sf::Vector2u window = config.getDimensions();
		if (canvas.getSize() != window) {
			std::cout << "Old Dimensions: " << canvas.getSize().x << " , " << canvas.getSize().y << std::endl;
			std::cout << "New Dimensions: " << window.x << " , " << window.y << std::endl;
			this->canvas.create(window.x, window.y);
		}
		Systems::EntityScriptSystem::OnUpdate(deltaTime, registry);
		Systems::WolfCollisionSystem(registry, map);
		/**
		* Additional Code Here
		*/
	}
	virtual void onFixedUpdate(float fixedDeltaTime) override{
		Systems::EntityScriptSystem::OnFixedUpdate(fixedDeltaTime, registry);

		/**
		* Additional Code Here
		*/
	}
	virtual sf::Sprite onRender() override {
		Config& config = Config::getConfig();
		Settings settings = config.getSettings();
		canvas.clear();
		Systems::DDARenderSystem::renderWalls(registry, map);
		Systems::RenderSystem2D(registry, canvas);
		//DONT REMOVE OR IT WILL BREAK LITERALLY EVERYTHING FOR SOME REASON
		this->player->draw(canvas,sf::Vector2f(50,50));
		Systems::EntityScriptSystem::OnRender(registry);
		canvasSprite.setTexture(canvas.getTexture());
		/**
		* Additional Code Here
		*/

		return canvasSprite;
	}
	virtual void onDestroy()override {
		/**
		* Additional Code Here
		 */
	}
	virtual void renderImGui() override {

	}
	virtual void renderEntitiesImGui() override
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

	~DDAScene(void) {
		this->onDestroy();	
	}
protected:
	PlayerController* playercontroller;
	TransformComponent* playerTransform;
	CameraComponent* cameraComponent;
	sf::RenderTexture playerScreen;
	Map map;
	int currentMap;
	std::shared_ptr<Player> player;
};

#endif