#pragma once
#include "imgui-SFML.h"
#include "imgui.h"
#include "CoreComponents.h"
#include "Components.h"
#include "Entity.h"

template<typename T>
void draw(T) {
	return;
}

template<>
void draw(TransformComponent transform) {
	if (ImGui::CollapsingHeader("Transform:")) {
		if (ImGui::CollapsingHeader("Position:"))
		{
			ImGui::InputFloat("X:", &transform.position.x);
			ImGui::InputFloat("Y:", &transform.position.y);
		}
		if (ImGui::CollapsingHeader("Rotation:"))
		{
			ImGui::InputFloat("X:", &transform.rotation.x);
			ImGui::InputFloat("Y:", &transform.rotation.y);
		}
	}
}

template<>
void draw(ControllableComponet controllableComponent) {
	if (ImGui::CollapsingHeader("Controllable Component: ")) {
		ImGui::Checkbox("Enabled:", &controllableComponent.enabled);
		ImGui::InputFloat("Sensitivity:", &controllableComponent.sensitivity);
		ImGui::InputFloat("Max Speed:", &controllableComponent.maxSpeed);
		ImGui::InputFloat("Movement Multipilier:", &controllableComponent.movementMultiplier);
		ImGui::InputFloat("Sprint Multiplier:", &controllableComponent.sprintMultiplier);
		ImGui::InputFloat("Turn Angle:", &controllableComponent.turnAngle);
	}
}

template<>
void draw(CameraComponent camCom) {
	if (ImGui::CollapsingHeader("Camera Component:")) {
		ImGui::InputFloat("FOV", &camCom.FOV, 5.0, 10.0);
		ImGui::InputFloat("Render Distance", &camCom.renderDistance);
		ImGui::InputFloat("Z Height", &camCom.zHeight);
		ImGui::Checkbox("Fisheye:", &camCom.fisheye);
		ImGui::Checkbox("Enabled:", &camCom.enabled);
		if (ImGui::CollapsingHeader("Plane:"))
		{
			std::string title = "X:" + std::to_string(camCom.plane.x);
			ImGui::Text(title.c_str());
			title = "Y:" + std::to_string(camCom.plane.y);
			ImGui::Text(title.c_str());
		}
	}
}