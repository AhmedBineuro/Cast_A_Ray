#include "Systems.h"

DVDLogoBehaviour::DVDLogoBehaviour() {
	spriteComponent = NULL;
	OnCreate();
}
void DVDLogoBehaviour::OnCreate() {
	std::cout << "DVDLogoBegavior OnCreate" << std::endl;
	velocity = sf::Vector2f();
	velocity.x = ((float)rand() / (float)RAND_MAX) * 100.0f - 5.0f;
	velocity.y = ((float)rand() / (float)RAND_MAX) * 100.0f - 5.0f;
}
void DVDLogoBehaviour::OnUpdate(float deltaTime) {
	move(deltaTime);
}
void DVDLogoBehaviour::OnFixedUpdate(float fixedDeltaTime) {
}
void DVDLogoBehaviour::OnRender() {
}
void DVDLogoBehaviour::OnDestroy() {
}
void DVDLogoBehaviour::move(float deltaTime) {
	if (spriteComponent == NULL)
		return;
	sf::FloatRect bounds;
	bounds = this->spriteComponent->sprite.getGlobalBounds();
	sf::Vector2f position = this->spriteComponent->sprite.getPosition();
	sf::Vector2u size = this->spriteComponent->sprite.getTexture()->getSize();
	sf::Vector2f scale = this->spriteComponent->sprite.getScale();
	//std::cout << "Position: " <<position.x<<" , "<< position.y << std::endl;
	if (position.x + ((float)size.x * scale.x) >= WINDOW_WIDTH || position.x <= 0)
		velocity.x *= -1;
	if (position.y + ((float)size.y * scale.y) >= WINDOW_HEIGHT || position.y <= 0)
		velocity.y *= -1;
	//std::cout << "Velocity: " << velocity.x << " , " << velocity.y << std::endl;
	position = position + (velocity * deltaTime);
	this->spriteComponent->sprite.setPosition(position);
}
DVDLogoBehaviour::~DVDLogoBehaviour() {
	OnDestroy();
}
