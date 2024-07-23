#include "Player.h"
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
	this->camera = nullptr;
	this->addComponent(ColliderComponent(transformComponent->position, sf::Vector2f(0.5f, 0.5f)));
	colliderComponent = this->getComponent<ColliderComponent>();
	this->addComponent(ScriptComponent(std::make_shared <PlayerController>(this, this->camera)));

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
	this->camera = nullptr;
	this->addComponent(ColliderComponent(transformComponent->position, sf::Vector2f(0.5f, 0.5f)));
	colliderComponent = this->getComponent<ColliderComponent>();
	this->addComponent(ScriptComponent(std::make_shared <PlayerController>(this,this->camera)));
}
void Player::setPosition(sf::Vector2f position){
	this->transformComponent->position = position;
	if(camera!=nullptr)
		this->camera->setPosition(this->transformComponent->position);
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
void Player::setCamera(Camera* cam)
{
	camera = cam;
	((PlayerController*)(getComponent<ScriptComponent>()->script).get())->setCamera(cam);
}
void Player::draw(sf::RenderTarget &canvas, sf::Vector2f tileSize) {
	sf::VertexArray line = sf::VertexArray(sf::Points, 1);
	line[0] = sf::Vertex();
	canvas.draw(line);
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