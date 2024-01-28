#include "RenderSystem2D.h"

RenderSystem2D::RenderSystem2D() {
	this->renderTarget = NULL;
}
RenderSystem2D::RenderSystem2D(sf::RenderTarget& renderTarget) {
	this->renderTarget = &renderTarget;
}
void RenderSystem2D::update(entt::registry& registry) {
	if (renderTarget == NULL)
		return;
	renderTarget->clear(sf::Color::White);
	//Get the list of entities with this component
	auto view = registry.view<RenderComponent, SpriteComponent>();
	for (auto entity : view) {
		RenderComponent renderComponent = registry.get<RenderComponent>(entity);
		if (renderComponent.enabled) {
			SpriteComponent& sprite = registry.get<SpriteComponent>(entity);
			renderTarget->draw(sprite.sprite, renderComponent.renderStates);
		}
	}
}