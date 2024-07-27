#include "Scene.h"

void Scene::renderImGui()
{
	ImGui::Begin("Scene Information##window");
	if (ImGui::BeginTabBar("Scene Information")) {
		if (ImGui::BeginTabItem("Scene Properites")) {
			
			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
		renderEntitiesImGui();
	}
	ImGui::End();
}

void Scene::renderEntitiesImGui()
{
	if (ImGui::BeginTabItem("Entity Settings")) {

		//Drag and drop to get scene canvas CHANGE LATER
		if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None)) {
			ImGui::SetDragDropPayload("_RNDR_TRGT_PTR_", (&canvas), sizeof(std::shared_ptr<sf::RenderTexture>));
			ImGui::Text("Dragging Scene canvas");
			ImGui::EndDragDropSource();
		}
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
			title = entity->getName();
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
				if (ImGui::Button("Delete Entity")) {
					this->entities.erase(this->entities.begin() + i);
					i -= 2;
				}
				ImGui::Unindent();
			}
			ImGui::PopID();
			i++;
		}
		ImGui::EndTabItem();
	}
}
