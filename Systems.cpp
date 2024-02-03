#include "Systems.h"

DVDLogoBehaviour::DVDLogoBehaviour() {
	spriteComponent = NULL;
	OnCreate();
}
void DVDLogoBehaviour::OnCreate() {
	velocity = sf::Vector2f(100,100);

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
	Config& config = Config::getConfig();
	Settings settings = config.getSettings();
	if (spriteComponent == NULL)
		return;
	sf::FloatRect bounds;
	bounds = this->spriteComponent->sprite.getGlobalBounds();
	sf::Vector2f position = this->spriteComponent->sprite.getPosition();
	sf::Vector2u size = this->spriteComponent->sprite.getTexture()->getSize();
	sf::Vector2f scale = this->spriteComponent->sprite.getScale();
	//std::cout << "Position: " <<position.x<<" , "<< position.y << std::endl;
	bool hit = false;
	if (position.x + ((float)size.x * scale.x) >= settings.width || position.x <= 0)
	{
		hit = true;
		velocity.x *= -1;
	}
	if (position.y + ((float)size.y * scale.y) >= settings.height || position.y <= 0)
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


