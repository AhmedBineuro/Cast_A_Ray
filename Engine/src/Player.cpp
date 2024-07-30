#include "Engine\include\Player.h"
Player::Player(entt::registry* registry) :Entity(registry){
	this->addComponent(TransformComponent());
	this->transformComponent = (this->getComponent<TransformComponent>());
	this->transformComponent->rotation = sf::Vector2f(1, 0);
	this->transformComponent->position = sf::Vector2f(25, 25);
	
	this->addComponent(SpriteComponent());
	this->spriteComponent = this->getComponent<SpriteComponent>();
	Resource_Manager& rm = Resource_Manager::getResourceManager();
	this->setSpriteTexture(rm.getTexture("PlayerSprite"));
	sf::Vector2u textSize = this->spriteComponent->sprite.getTexture()->getSize();
	this->spriteComponent->sprite.setOrigin((float)textSize.x / 2.0f, (float)textSize.y / 2.0f);
	sf::Vector2f spriteSize = sf::Vector2f(25, 25);
	setSpriteSize(spriteSize);

	this->addComponent(ControllableComponent());
	this->transformComponent->rotation = sf::Vector2f(1, 0);
	this->controllable = this->getComponent<ControllableComponent>();
	this->camera = std::weak_ptr<Camera>();
	this->addComponent(ColliderComponent(transformComponent->position, sf::Vector2f(0.5f, 0.5f)));
	colliderComponent = this->getComponent<ColliderComponent>();
	this->addComponent(ScriptComponent(std::make_shared <PlayerController>(this, this->camera.lock().get())));

}
Player::Player(entt::registry* registry, sf::Vector2f position) :Entity(registry) {
	this->addComponent(TransformComponent());
	this->transformComponent = (this->getComponent<TransformComponent>());
	this->transformComponent->position = position;
	this->transformComponent->rotation = sf::Vector2f(1, 0);

	this->addComponent(SpriteComponent());
	this->spriteComponent = this->getComponent<SpriteComponent>();
	Resource_Manager& rm = Resource_Manager::getResourceManager();
	this->setSpriteTexture(rm.getTexture("PlayerSprite"));
	sf::Vector2u textSize = this->spriteComponent->sprite.getTexture()->getSize();
	this->spriteComponent->sprite.setOrigin((float)textSize.x / 2.0f, (float)textSize.y / 2.0f);
	sf::Vector2f spriteSize = sf::Vector2f(25, 25);
	setSpriteSize(spriteSize);

	this->addComponent(ControllableComponent());
	this->transformComponent->rotation = sf::Vector2f(1, 0);
	this->controllable = this->getComponent<ControllableComponent>();
	this->camera = std::weak_ptr<Camera>();
	this->addComponent(ColliderComponent(transformComponent->position, sf::Vector2f(0.5f, 0.5f)));
	colliderComponent = this->getComponent<ColliderComponent>();
	this->addComponent(ScriptComponent(std::make_shared <PlayerController>()));
}
void Player::setPosition(sf::Vector2f position){
	this->transformComponent->position = position;
	if(this->camera.lock())
		this->camera.lock()->setPosition(this->transformComponent->position);
	this->colliderComponent->border.top = this->transformComponent->position.y - (this->colliderComponent->border.height/2);
	this->colliderComponent->border.left = this->transformComponent->position.x - (this->colliderComponent->border.width / 2);
}
void Player::setSpriteSize(sf::Vector2f newSize)
{
	sf::Vector2u size = this->spriteComponent->sprite.getTexture()->getSize();
	sf::Vector2f scale(newSize.x / (float)size.x, newSize.y / (float)size.y);
	this->spriteComponent->sprite.setScale(scale);
	this->spriteSize.x = newSize.x;
	this->spriteSize.y = newSize.y;
}
void Player::setCamera(std::shared_ptr<Camera> cam)
{
	camera = std::weak_ptr<Camera>(cam);
	if(camera.lock())
		((PlayerController*)(getComponent<ScriptComponent>()->script).get())->setCamera(camera.lock());
}
void Player::setSpriteTexture(sf::Texture& texture) {
	this->spriteComponent->sprite.setTexture(texture);
	sf::Vector2u textSize = texture.getSize();
	sf::Vector2f scale(spriteSize.x / (float)textSize.x, spriteSize.y / (float)textSize.y);
	this->spriteComponent->sprite.setScale(scale);
	this->spriteComponent->sprite.setOrigin((float)textSize.x / 2.0f, (float)textSize.y / 2.0f);
}
Player::~Player() {
	
}