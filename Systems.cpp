#include "Systems.h"

DVDLogoBehaviour::DVDLogoBehaviour() {
	spriteComponent = NULL;
	OnCreate();
}
void DVDLogoBehaviour::OnCreate() {
	velocity = sf::Vector2f(100,100);
	Config& config = Config::getConfig();
	screenDimensions = config.getDimensions();
	}
void DVDLogoBehaviour::OnUpdate(float deltaTime) {
	Config& config = Config::getConfig();
	sf::Vector2u newScreenDimensions= config.getDimensions();
	if (screenDimensions != newScreenDimensions)
	{
		//Get position size ratios to place it in the correct place at the correcr size
		sf::Vector2u textureSize = this->spriteComponent->sprite.getTexture()->getSize();
		sf::Vector2f oldScale = this->spriteComponent->sprite.getScale();
		sf::Vector2f size(textureSize.x*oldScale.x, textureSize.y * oldScale.y);
		sf::Vector2f position(this->spriteComponent->sprite.getPosition());
		sf::Vector2f ratioPos(position.x / (float)screenDimensions.x, position.y / (float)screenDimensions.y);
		sf::Vector2f ratioSize(size.x / (float)screenDimensions.x, size.y / (float)screenDimensions.y);
		this->spriteComponent->sprite.setPosition(sf::Vector2f(newScreenDimensions.x * ratioPos.x, newScreenDimensions.y * ratioPos.y));
		float scaleX = (float)newScreenDimensions.x*ratioSize.x / (float)textureSize.x;
		float scaleY = (float)newScreenDimensions.y * ratioSize.y / (float)textureSize.y;
		this->spriteComponent->sprite.setScale(sf::Vector2f(scaleX, scaleY));
		screenDimensions = newScreenDimensions;
	}
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
	sf::Vector2f position = this->spriteComponent->sprite.getPosition();
	sf::Vector2u size = this->spriteComponent->sprite.getTexture()->getSize();
	sf::Vector2f scale = this->spriteComponent->sprite.getScale();
	//std::cout << "Position: " <<position.x<<" , "<< position.y << std::endl;
	bool hit = false;
	if (position.x + ((float)size.x * scale.x) >= screenDimensions.x || position.x <= 0)
	{
		hit = true;
		velocity.x *= -1;
	}
	if (position.y + ((float)size.y * scale.y) >= screenDimensions.y || position.y <= 0)
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


