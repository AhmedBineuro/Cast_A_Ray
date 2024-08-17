#pragma once
#include "CoreComponents.h"
#include "Scene.h"
#include "imgui.h"
#include "imgui-SFML.h"

namespace ImGui {
	void draw(Component*);
	void draw(TransformComponent*);
	void draw(IntegratedScriptComponent*);
	void draw(RenderStatesComponent*);
	void draw(SpriteComponent*);
	void draw(ControllableComponent*);
	void draw(CameraComponent*);
	void draw(MapTagComponent*);
	void draw(ColliderComponent*);
	void draw(CanvasComponent*);
	void draw(Scene*);
};