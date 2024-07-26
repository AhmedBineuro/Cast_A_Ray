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
		std::shared_ptr<Camera> cam;
		cam = std::make_shared<Camera>(&this->registry, sf::Vector2f(2, 2));
		this->entities.push_back(player);
		this->entities.push_back(cam);
		player->setCamera(cam);
		this->player->setName("Player");
		this->player->camera.lock()->setName("Player Camera");
		this->player->camera.lock()->linkRenderTarget(&this->canvas);
		this->map = Map();
		this->onCreate();
	}
	DDAScene(std::string mapName) :Scene2D() {
		this->map = Map(mapName);
		std::shared_ptr<Camera> cam;
		cam = std::make_shared<Camera>(&this->registry, sf::Vector2f(2, 2));
		this->player = std::make_shared<Player>(&this->registry, sf::Vector2f(2, 2));
		this->entities.push_back(player);
		this->entities.push_back(cam);
		player->setCamera(cam);
		
		this->player->camera.lock()->linkRenderTarget(&this->canvas);
		this->player->setName("Player");
		this->player->camera.lock()->setName("Player Camera");
		this->onCreate();
	}
	virtual void onCreate() override{
		currentMap = 0;
		this->playerTransform = player->getComponent<TransformComponent>();
		this->cameraComponent = this->player->camera.lock()->getComponent<CameraComponent>();
		playercontroller = this->player->getComponent<PlayerController>();
		/**
		* Additional Code Here
		*/
	}
	virtual void onUpdate(float deltaTime) override{
		Config& config = Config::getConfig();
		sf::Vector2u canvSize = config.getRenderResolution();
		if (canvas.getSize() != canvSize) {
			this->canvas.create(canvSize.x, canvSize.y);
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
		ImGui::Begin("Scene Information##window");
		if(ImGui::BeginTabBar("Scene Information")) {
			renderEntitiesImGui();
			if (ImGui::BeginTabItem("Scene Properites")) {
				ImGui::EndTabItem();
			}
			ImGui::EndTabBar();
		}
		ImGui::End();
	}
	virtual void renderEntitiesImGui() override
	{
		if (ImGui::BeginTabItem("Entity Settings")){
			if (ImGui::Button("Add Entity")) {
				std::shared_ptr<Entity> newEnt = std::make_shared<Entity>(&this->registry);
				this->entities.push_back((newEnt));
			}
			ImGui::Separator();
			int i = 0;
			for (auto entity : this->entities)
			{
				if (entity == NULL)
					continue;
				std::string title;
				title.resize(20);
				title= entity->getName();
				ImGui::PushID((unsigned int)entity->getHandle());
				if (ImGui::CollapsingHeader(title.c_str()))
				{
					if (ImGui::BeginDragDropSource()) {
						ImGui::SetDragDropPayload("_ENTITY_PTR_", &entity, sizeof(entity));
						ImGui::Text("Dragging %s", entity->getName().c_str());
						ImGui::EndDragDropSource();
					}
					ImGui::Indent();
					entity->drawImGui();
					ImGui::Unindent();
					if (ImGui::Button("Delete Entity")) {
						printf("Current Index and Handle %d, %u\n", i, (unsigned int)entity->getHandle());
						this->entities.erase(this->entities.begin() + i);
						i-=2;
					}
				}
				ImGui::PopID();
				i++;
			}
			ImGui::EndTabItem();
		}
	}
	void onEventLoop(sf::Event event) override{
		Systems::EntityScriptSystem::OnEventLoop(registry,event);
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