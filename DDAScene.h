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
		this->entities.push_back(player);
		this->player->camera->linkRenderTarget(&this->canvas);
		this->map = Map();
		this->onCreate();
	}
	DDAScene(std::string mapName) :Scene2D() {
		this->map = Map(mapName);
		this->player = std::make_shared<Player>(&this->registry, sf::Vector2f(2, 2));
		this->entities.push_back(player);
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
		this->map.draw(canvas);
		Systems::RenderSystem2D(registry, canvas);
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
	virtual void renderDebug() override {
		//if(ImGui::BeginTabBar("Entity Settings"))
		//{
		//	int i = 0;
		//	for (auto entity: this->entities)
		//	{
		//		/*std::string title = "Entity number" + std::to_string(i);
		//		if(ImGui::CollapsingHeader(title.c_str()))
		//		{
		//			entity->drawDebug();
		//		}*/
		//	}
		//	ImGui::EndTabBar;
		//}
		if(ImGui::BeginTabItem("Player Settings: ")) {
			ImGui::PushID((uint32_t)(player->getHandle()));
			player->getComponent<TransformComponent>()->draw();
			player->getComponent<ColliderComponent>()->draw();
			player->getComponent<ControllableComponent>()->draw();
			ImGui::PopID();
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Camera Settings: ") && player->camera!=nullptr) {
			ImGui::PushID((uint32_t)(player->camera->getHandle()));
			player->camera->getComponent<TransformComponent>()->draw();
			player->camera->getComponent<CameraComponent>()->draw();
			ImGui::PopID();
			ImGui::EndTabItem();
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