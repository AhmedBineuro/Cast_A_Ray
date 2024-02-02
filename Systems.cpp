#include "Systems.h"

DVDLogoBehaviour::DVDLogoBehaviour() {
	spriteComponent = NULL;
	OnCreate();
}
void DVDLogoBehaviour::OnCreate() {
	velocity = sf::Vector2f(100,100);
	//velocity.x = ((float)rand() / (float)RAND_MAX) * 100.0f - 5.0f;
	//velocity.y = ((float)rand() / (float)RAND_MAX) * 100.0f - 5.0f;

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
	bool hit = false;
	if (position.x + ((float)size.x * scale.x) >= WINDOW_WIDTH || position.x <= 0)
	{
		hit = true;
		velocity.x *= -1;
	}
	if (position.y >= WINDOW_HEIGHT || position.y + ((float)size.y * scale.y) <= 0)
	{
		hit = true;
		velocity.y *= -1;
	}
	if (hit) {
		int r = rand() / (float)RAND_MAX * 255 + 1;
		int g = rand() / (float)RAND_MAX * 255 + 1;
		int b = rand() / (float)RAND_MAX * 255 + 1;
		spriteComponent->sprite.setColor(sf::Color(r, g, b));
	}
	//std::cout << "Velocity: " << velocity.x << " , " << velocity.y << std::endl;
	position = position + (velocity * deltaTime);
	this->spriteComponent->sprite.setPosition(position);
}
DVDLogoBehaviour::~DVDLogoBehaviour() {
	OnDestroy();
}
//////////////////////////////////////////


