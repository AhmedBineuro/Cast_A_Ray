#include "RenderSystem2D.h"

RenderSystem2D::RenderSystem2D() {
	this->renderTarget = NULL;
}
RenderSystem2D::RenderSystem2D(sf::RenderTexture& renderTarget) {
	this->renderTarget = &renderTarget;
}
void RenderSystem2D::update(entt::registry& registry) {
	if (renderTarget == NULL)
		return;
	//Get the list of entities with this component
	auto view = registry.view<RenderComponent, SpriteComponent,TransformComponent>();
	for (auto entity : view) {
		RenderComponent renderComponent = registry.get<RenderComponent>(entity);
		if (renderComponent.enabled) {
			TransformComponent transformComponent = registry.get<TransformComponent>(entity);
			SpriteComponent& sprite = registry.get<SpriteComponent>(entity);
			sprite.sprite.setPosition(transformComponent.position);
			sprite.sprite.setRotation(sf::getRotationAngle(transformComponent.rotation));
			renderTarget->draw(sprite.sprite, renderComponent.renderStates);
		}
	}
	renderTarget->display();
}
void RenderSystem2D::setTarget(sf::RenderTexture* target) {
	this->renderTarget = target;
}