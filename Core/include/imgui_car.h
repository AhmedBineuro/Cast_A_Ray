#pragma once
#include "Core\include\CoreComponents.h"

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
}
