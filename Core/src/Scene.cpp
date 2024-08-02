#include "Core\include\Scene.h"

void Scene::renderImGui()
{
	ImGui::Begin("Scene Properites");
	std::set<std::string> names;
	names.clear();
	for (auto name = this->canvasMap.begin(); name != this->canvasMap.end(); name++)
		names.insert(name->first);

	if (ImGui::Button("Create Canvas##canvas_create_button")) {
		ImGui::OpenPopup("Create Canvas##popup");
	}


	if (ImGui::BeginPopupModal("Create Canvas##popup", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
		ImGui::Text("Name");
		ImGui::SameLine();
		static char canvSel_name[16] = "";
		ImGui::InputText("##canvas_name", canvSel_name, sizeof(canvSel_name));
		if (this->canvasMap.find(canvSel_name) != this->canvasMap.end()) {
			ImGui::Text("Error: the name already exists");
		}
		ImGui::Spacing();
		ImGui::Text("Dimensions");
		static int dimensions[2] = {100, 100};
		ImGui::InputInt2("##canvas_dimensions", dimensions);
		ImGui::Spacing();

		if (ImGui::Button("Create##final_create"))
		{

			if(this->canvasMap.find(canvSel_name) == this->canvasMap.end()){

				this->canvasMap[canvSel_name] = std::make_shared<sf::RenderTexture>();
				this->canvasMap[canvSel_name]->create(dimensions[0], dimensions[1]);
					
				canvSel_name[0] = '\0';
				dimensions[0] = 100;
				dimensions[1] = 100;
				ImGui::CloseCurrentPopup(); 
			}
		}
			ImGui::SameLine();
		if (ImGui::Button("Cancel##final_create_cancel")) 
		{ 
			canvSel_name[0] = '\0';
			dimensions[0] = 100;
			dimensions[1] = 100;
			ImGui::CloseCurrentPopup(); 
		}
				
		ImGui::EndPopup();
	}
			


	ImGui::Text("Main canvas:");
	ImGui::SameLine();
	if (ImGui::BeginCombo("##sceneSelector", this->currentCanvas.c_str())) {
		for (auto name : names) {
			if (ImGui::Button(("X##del" + name).c_str())) {
				ImGui::OpenPopup(("Remove Canvas##popup"+name).c_str());
			}
			if (ImGui::BeginPopupModal(("Remove Canvas##popup" + name).c_str(),nullptr,ImGuiWindowFlags_AlwaysAutoResize| ImGuiWindowFlags_NoResize)) {
				ImGui::Text("Are you sure you want to delete %s", name.c_str());
				if (ImGui::Button(("Remove##final_remove_" + name).c_str())) {
					canvasMap.erase(name);
					ImGui::CloseCurrentPopup();
				}
				ImGui::SameLine();
				if (ImGui::Button(("Cancel##final_remove_cancel_" + name).c_str())) { 
					ImGui::CloseCurrentPopup(); 
				}
				ImGui::EndPopup();
			}
			ImGui::SameLine();
			static char newName[16];
			static int newDimensions[2];
			if (ImGui::Button(("Edit##Ed" + name).c_str())) {
						
				sf::Vector2u dimVec = (this->canvasMap[name] != nullptr) ? this->canvasMap[name]->getSize() : sf::Vector2u();
				newDimensions[0] = dimVec.x;
				newDimensions[1] = dimVec.y;
						
				for (int i = 0; i < name.size(); i++)
					newName[i] = name[i];
				newName[name.size()] = '\0';
				ImGui::OpenPopup(("Edit Canvas##Ed" + name).c_str());
			}
			if (ImGui::BeginPopupModal(("Edit Canvas##Ed" + name).c_str(), nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize)) {
				ImGui::InputText("##canvas_name", newName, sizeof(newName));
				if (this->canvasMap.find(newName) != this->canvasMap.end()) {
					ImGui::Text("Error: the name already exists");
				}
				ImGui::Spacing();
				ImGui::Text("Dimensions");
				ImGui::InputInt2("##canvas_new_dimensions",newDimensions);
				ImGui::Spacing();
				if (ImGui::Button(("Apply##Ed_apply" + name).c_str())) {
					auto entry=this->canvasMap.extract(name);
					entry.key() = newName;
					this->canvasMap.insert(std::move(entry));
					if (this->canvasMap[newName] == nullptr)
						this->canvasMap[newName] = std::make_shared<sf::RenderTexture>();
					this->canvasMap[newName]->create(newDimensions[0], newDimensions[1]);
					ImGui::CloseCurrentPopup();
				}
				ImGui::SameLine();
				if (ImGui::Button(("Cancel##Ed_apply" + name).c_str())) {
					ImGui::CloseCurrentPopup();
				}
				ImGui::EndPopup();
			}
			ImGui::SameLine();
			bool is_selected = (name.compare(currentCanvas) == 0);
			if (ImGui::Selectable(name.c_str(), is_selected))
			{
				this->currentCanvas = name;
			}
			if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None)) {
				Canvas canvas = {
					
				};
				Canvas payload = Canvas(this->canvasMap[name], name);
				ImGui::SetDragDropPayload("_CANVAS_TRGT_PTR_", &(payload), sizeof(Canvas));
				ImGui::Text("Dragging canvas: %s",name.c_str());
				ImGui::EndDragDropSource();
			}

			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}
	ImGui::End();
	renderEntitiesImGui();
}

void Scene::renderEntitiesImGui()
{
	ImGui::Begin("Entity Settings");
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

			if (ImGui::Button("Add Component##addComponent")) {
				ImGui::OpenPopup("Component_List");
			}
				
			//Menu to add the components on the fly
			if (ImGui::BeginPopup("Component_List")) {
				if (ImGui::MenuItem("Transform Component")) {
					entity->addComponent(TransformComponent());
				}
				if (ImGui::MenuItem("Player Controller Script Component")) {
					entity->addComponent(IntegratedScriptComponent(std::make_shared<PlayerController>()));
				}
				if (ImGui::MenuItem("Sprite Component")) {
					entity->addComponent(SpriteComponent());
				}
				if (ImGui::MenuItem("Controllable Component")) {
					entity->addComponent(ControllableComponent());
				}
				if (ImGui::MenuItem("Render States Component")) {
					entity->addComponent(RenderStatesComponent());
				}
				if (ImGui::MenuItem("Camera Component")) {
					entity->addComponent(CameraComponent());
				}
				if (ImGui::MenuItem("Canvas Component")) {
					entity->addComponent(CanvasComponent());
				}
				if (ImGui::MenuItem("Map Tag Component")) {
					entity->addComponent(MapTagComponent());
				}
				if (ImGui::MenuItem("Collider Component")) {
					entity->addComponent(ColliderComponent());
				}
				ImGui::EndPopup();
			}

			//Draw 
			ImGui::Text("Name:");
			ImGui::SameLine();
			if (!ImGui::InputText("##input", entity->buffer.begin()._Unwrapped(), 20));
			if (!ImGui::IsWindowFocused())
			{
				entity->buffer = entity->getName();
				entity->buffer.resize(20);
			}
			ImGui::SameLine();
			if (ImGui::Button("apply##name")) {
				entity->setName(entity->buffer);
			}
			//entity->drawImGui();
			for (auto component : *(entity->getComponentList()))
				component->draw();
			if (ImGui::Button("Delete Entity")) {
				this->entities.erase(this->entities.begin() + i);
				i -= 2;
			}
			ImGui::Unindent();
		}
		ImGui::PopID();
		i++;
	}
	ImGui::End();
}
