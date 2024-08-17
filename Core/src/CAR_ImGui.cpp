#include "./Core/include/CAR_ImGui.h"
namespace ImGui {
	void draw(Component*c){
		std::string name = c->componentName;
		if (!name.compare("Transform Component")) {
			ImGui::draw((TransformComponent*)c);
		}
		else if (!name.compare("IntScript Component")) {
			ImGui::draw((IntegratedScriptComponent*)c);
		}
		else if (!name.compare("RendStates Component")) {
			ImGui::draw((RenderStatesComponent*)c);
		}
		else if (!name.compare("Sprite Component")) {
			ImGui::draw((SpriteComponent*)c);
		}
		else if (!name.compare("Controllable Component")) {
			ImGui::draw((ColliderComponent*)c);
		}
		else if (!name.compare("Camera Component")) {
			ImGui::draw((CameraComponent*)c);
		}
		else if (!name.compare("MapTag Component")) {
			ImGui::draw((MapTagComponent*)c);
		}
		else if (!name.compare("Collider Component")) {
			ImGui::draw((ColliderComponent*)c);
		}
		else if (!name.compare("Canvas Component")) {
			ImGui::draw((CanvasComponent*)c);
		}
	}
	void draw(TransformComponent*c){
		if (ImGui::CollapsingHeader("Transform Component")) {
			ImGui::Indent();
			ImGui::Text("Position: ");

			ImGui::PushItemWidth(80);
			ImGui::InputFloat("X##Pos", &c->position.x);
			ImGui::InputFloat("Y##Pos", &c->position.y);
			ImGui::PopItemWidth();

			static float angle = sf::getRotationAngle(c->rotation);
			if (ImGuiKnobs::Knob("Rotation:", &angle, 0, 360, 0.5f, 0, 1, 0, ImGuiKnobFlags_DragHorizontal)) {
				c->rotation = sf::getAbsoluteRotated(angle);
			}
			ImGui::Unindent();
		}
	}
	void draw(IntegratedScriptComponent*c){
		if (ImGui::CollapsingHeader("Integrated Script Component")) {
			ImGui::Indent();
			int i = 0;
			for (auto script : c->scripts)
			{
				if (ImGui::Button("X")) {
					c->scripts.erase(c->scripts.begin() + i);
					i -= 2;
				}
				ImGui::SameLine();
				script->renderImGui();
				i++;
			}
			ImGui::Checkbox("Enabled##script", &c->enabled);
			ImGui::Unindent();
		}
	}
	void draw(RenderStatesComponent* c) {
		if (ImGui::CollapsingHeader("Render States Component")) {
			ImGui::Indent();
			ImGui::Checkbox("Enabled##Render", &c->enabled);
			ImGui::Unindent();
		}
	}
	void draw(SpriteComponent*c){
		if (ImGui::CollapsingHeader("Sprite Component")) {
			ImGui::Indent();
			ImGui::Unindent();
		}
	}
	void draw(ControllableComponent*c){
		if (ImGui::CollapsingHeader("Controllable Component")) {
			ImGui::Indent();
			ImGui::Checkbox("Enabled##Controllable", &c->enabled);

			ImGui::PushItemWidth(80);
			ImGui::InputFloat("Max Speed", &c->maxSpeed);

			ImGui::InputFloat("Movement Multiplier", &c->movementMultiplier);

			ImGui::InputFloat("Sprint Multiplier", &c->sprintMultiplier);

			ImGui::InputFloat("Turn angle", &c->turnAngle);

			ImGui::InputFloat("Sensitivity", &c->sensitivity);
			ImGui::PopItemWidth();
			ImGui::Unindent();
		}
	}
	void draw(CameraComponent*c){
		if (ImGui::CollapsingHeader("Camera Component")) {
			ImGui::Indent();
			ImGui::Text("Plane: x:%f , y:%f", c->plane.x, c->plane.y);
			ImGui::PushItemWidth(80);
			if (ImGui::InputFloat("FOV", &c->FOV)) {
				c->updatePlane();
			}

			ImGui::InputFloat("Render Distance", &c->renderDistance);

			ImGui::InputFloat("Vertical Height", &c->zHeight);
			ImGui::PopItemWidth();
			ImGui::Checkbox("Fisheye", &c->fisheye);

			ImGui::Checkbox("Enable##Camera", &c->enabled);
		}
	}
	void draw(MapTagComponent* c) {
		if (ImGui::CollapsingHeader("Map Tag Component")) {
			ImGui::Indent();
			ImGui::Unindent();
		}
	}
	void draw(ColliderComponent*c){
		if (ImGui::CollapsingHeader("Collider Component")) {
			ImGui::Indent();
			ImGui::Text("Collider Dimensions:");

			ImGui::PushItemWidth(80);

			ImGui::InputFloat("X##width", &c->border.width);
			ImGui::InputFloat("Y##height", &c->border.height);

			ImGui::Text("Collider Position:");
			ImGui::InputFloat("X##left", &c->border.left);
			ImGui::InputFloat("Y##top", &c->border.top);
			ImGui::PopItemWidth();

			ImGui::Checkbox("Is Trigger", &c->isTrigger);
			ImGui::Checkbox("Enabled##Collider", &c->enabled);
			ImGui::Unindent();
		}
	}
	void draw(CanvasComponent*c) {
		if (ImGui::CollapsingHeader("Canvas Component")) {
			ImGui::Indent();
			ImGui::Text("Current canvas: %s",
				((c->canvas.lock()) ? c->canvasName.c_str() : "None"));
			if (ImGui::BeginDragDropTarget()) {
				if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("_CANVAS_TRGT_PTR_")) {
					Canvas can = *static_cast<const Canvas*>(payload->Data);
					std::weak_ptr<sf::RenderTexture> wptr = std::weak_ptr(can.target);
					if (!wptr.lock())
					{
						printf("Bad Texture\n");
					}
					else {
						c->canvas = wptr.lock();
						c->canvasName = can.name;
					}
					ImGui::Text("Target Assigned");
					ImGui::EndDragDropTarget();
				}
				ImGui::Unindent();
			}
			ImGui::Unindent();
		}
	}
	void draw(Scene* s) {
		//Scene Settings
		ImGui::Begin("Scene Properites", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
		std::set<std::string> names;
		names.clear();
		for (auto name = s->canvasMap.begin(); name != s->canvasMap.end(); name++)
			names.insert(name->first);

		if (ImGui::Button("Create Canvas##canvas_create_button")) {
			ImGui::OpenPopup("Create Canvas##popup");
		}

		//Create canvas popup
		if (ImGui::BeginPopupModal("Create Canvas##popup", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
			ImGui::Text("Name");
			ImGui::SameLine();
			static char canvSel_name[16] = "";
			ImGui::InputText("##canvas_name", canvSel_name, sizeof(canvSel_name));
			if (s->canvasMap.find(canvSel_name) != s->canvasMap.end()) {
				ImGui::Text("Error: the name already exists");
			}
			else if (strcmp(canvSel_name, "") == 0) {
				ImGui::Text("Name is required to create canvas");
			}
			ImGui::Spacing();
			ImGui::Text("Dimensions");
			static int dimensions[2] = { 100, 100 };
			ImGui::InputInt2("##canvas_dimensions", dimensions);
			ImGui::Spacing();

			if (ImGui::Button("Create##final_create"))
			{

				if (s->canvasMap.find(canvSel_name) == s->canvasMap.end() && strcmp(canvSel_name, "") != 0) {

					s->createCanvas(canvSel_name, dimensions[0], dimensions[1]);

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
		//Canvas list combo
		if (ImGui::BeginCombo("##canvasSelector", s->currentCanvas.c_str())) {
			for (auto name : names) {
				if (ImGui::Button(("X##del" + name).c_str())) {
					ImGui::OpenPopup(("Remove Canvas##popup" + name).c_str());
				}
				//Remove canvas popup
				if (ImGui::BeginPopupModal(("Remove Canvas##popup" + name).c_str(), nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize)) {
					ImGui::Text("Are you sure you want to delete %s", name.c_str());
					if (ImGui::Button(("Remove##final_remove_" + name).c_str())) {
						s->deleteCanvas(name);
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

					sf::Vector2u dimVec = (s->canvasMap[name] != nullptr) ? s->canvasMap[name]->getSize() : sf::Vector2u();
					newDimensions[0] = dimVec.x;
					newDimensions[1] = dimVec.y;

					for (int i = 0; i < name.size(); i++)
						newName[i] = name[i];
					newName[name.size()] = '\0';
					ImGui::OpenPopup(("Edit Canvas##Ed" + name).c_str());
				}
				//Edit canvas popup
				if (ImGui::BeginPopupModal(("Edit Canvas##Ed" + name).c_str(), nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize)) {
					ImGui::InputText("##canvas_name", newName, sizeof(newName));
					if (s->canvasMap.find(newName) != s->canvasMap.end()) {
						ImGui::Text("Error: the name already exists");
					}
					ImGui::Spacing();
					ImGui::Text("Dimensions");
					ImGui::InputInt2("##canvas_new_dimensions", newDimensions);
					ImGui::Spacing();
					if (ImGui::Button(("Apply##Ed_apply" + name).c_str())) {
						auto entry = s->canvasMap.extract(name);
						entry.key() = newName;
						s->canvasMap.insert(std::move(entry));
						if (s->canvasMap[newName] == nullptr)
							s->canvasMap[newName] = std::make_shared<sf::RenderTexture>();
						s->canvasMap[newName]->create(newDimensions[0], newDimensions[1]);
						ImGui::CloseCurrentPopup();
					}
					ImGui::SameLine();
					if (ImGui::Button(("Cancel##Ed_apply" + name).c_str())) {
						ImGui::CloseCurrentPopup();
					}
					ImGui::EndPopup();
				}
				ImGui::SameLine();
				bool is_selected = (name.compare(s->currentCanvas) == 0);
				if (ImGui::Selectable(name.c_str(), is_selected))
				{
					s->currentCanvas = name;
				}
				if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None)) {
					Canvas canvas = {

					};
					Canvas payload = Canvas(s->canvasMap[name], name);
					ImGui::SetDragDropPayload("_CANVAS_TRGT_PTR_", &(payload), sizeof(Canvas));
					ImGui::Text("Dragging canvas: %s", name.c_str());
					ImGui::EndDragDropSource();
				}

				if (is_selected)
					ImGui::SetItemDefaultFocus();
			}
			ImGui::EndCombo();
		}
		ImGui::End();
			
		//Entity Settings
		ImGui::Begin("Entity Settings", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
		if (ImGui::Button("Add Entity")) {
			s->addEntity();
		}
		ImGui::Separator();
		int i = 0;
		for (auto entity : s->entities)
		{
			if (entity == NULL)
				continue;
			std::string title;
			title.resize(20);
			title = entity->getName();
			ImGui::PushID((unsigned int)entity->getHandle());
			if (ImGui::Button("X##delEntity")) {
				s->removeEntity(entity->getHandle());
				i -= 2;
			}
			ImGui::SameLine();
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
						if (!entity->hasComponent<TransformComponent>())
							entity->addComponent(TransformComponent());
					}
					if (ImGui::MenuItem("Integrated Script Component")) {
						if (!entity->hasComponent<IntegratedScriptComponent>())
							entity->addComponent(IntegratedScriptComponent());
					}
					if (ImGui::MenuItem("Player Controller Script")) {
						if (!entity->hasComponent<IntegratedScriptComponent>())
							entity->addComponent(IntegratedScriptComponent());
						auto scrptComp = entity->getComponent<IntegratedScriptComponent>();
						scrptComp->scripts.push_back(std::make_shared<PlayerController>());
					}
					if (ImGui::MenuItem("Sprite Component")) {
						if (!entity->hasComponent<SpriteComponent>())
							entity->addComponent(SpriteComponent());
					}
					if (ImGui::MenuItem("Controllable Component")) {
						if (!entity->hasComponent<ControllableComponent>())
							entity->addComponent(ControllableComponent());
					}
					if (ImGui::MenuItem("Render States Component")) {
						if (!entity->hasComponent<RenderStatesComponent>())
							entity->addComponent(RenderStatesComponent());
					}
					if (ImGui::MenuItem("Camera Component")) {
						if (!entity->hasComponent<CameraComponent>())
							entity->addComponent(CameraComponent());
					}
					if (ImGui::MenuItem("Canvas Component")) {
						if (!entity->hasComponent<CanvasComponent>())
							entity->addComponent(CanvasComponent());
					}
					if (ImGui::MenuItem("Map Tag Component")) {
						if (!entity->hasComponent<MapTagComponent>())
							entity->addComponent(MapTagComponent());
					}
					if (ImGui::MenuItem("Collider Component")) {
						if (!entity->hasComponent<ColliderComponent>())
							entity->addComponent(ColliderComponent());
					}
					ImGui::EndPopup();
				}

				//Draw 
				ImGui::Text("Name:");
				ImGui::SameLine();
				ImGui::PushItemWidth(120);
				if (!ImGui::InputText("##input", entity->buffer.begin()._Unwrapped(), 20));
				ImGui::PopItemWidth();
				if (!ImGui::IsWindowFocused())
				{
					entity->buffer = entity->getName();
					entity->buffer.resize(20);
				}
				ImGui::SameLine();
				if (ImGui::Button("apply##name")) {
					entity->setName(entity->buffer);
				}
				for (auto component : *(entity->getComponentList()))
					ImGui::draw(component);
				ImGui::Unindent();
			}
			ImGui::PopID();
			i++;
		}
		ImGui::End();
	}
}