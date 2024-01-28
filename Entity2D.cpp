#include "Entity2D.h"
#include "Resource_Manager.h"

DVDLogoBehaviour::DVDLogoBehaviour(){
	sprite = NULL;
	OnCreate();
}
void DVDLogoBehaviour::OnCreate() {
	std::cout << "DVDLogoBegavior OnCreate"<<std::endl;
	velocity = sf::Vector2f();
	velocity.x = ((float)rand() / (float)RAND_MAX) * 100.0f - 5.0f;
	velocity.y= ((float)rand() / (float)RAND_MAX) * 100.0f - 5.0f;
}
void DVDLogoBehaviour::OnUpdate(float deltaTime){
	move(deltaTime);
}
void DVDLogoBehaviour::OnFixedUpdate(float fixedDeltaTime) {
}
void DVDLogoBehaviour::OnRender() {
}
void DVDLogoBehaviour::OnDestroy() {
}
void DVDLogoBehaviour::move(float deltaTime) {
	if (sprite == NULL)
		return;
	sf::FloatRect bounds;
	bounds = sprite->getGlobalBounds();
	sf::Vector2f position = sprite->getPosition();
	sf::Vector2u size = sprite->getTexture()->getSize();
	sf::Vector2f scale = sprite->getScale();
	//std::cout << "Position: " <<position.x<<" , "<< position.y << std::endl;
	if (position.x + ((float)size.x * scale.x) >= WINDOW_WIDTH || position.x <= 0)
		velocity.x *= -1;
	if (position.y + ((float)size.y * scale.y) >= WINDOW_HEIGHT || position.y <= 0)
		velocity.y *= -1;
	//std::cout << "Velocity: " << velocity.x << " , " << velocity.y << std::endl;
	position = position + (velocity*deltaTime);
	sprite->setPosition(position);
}
DVDLogoBehaviour::~DVDLogoBehaviour(){
	OnDestroy();
}
//////////////////////////////////////////////////////////
Entity2D::Entity2D(entt::registry* registry):Entity(registry){
	this->addComponent(ScriptComponent(std::make_shared<DVDLogoBehaviour>()));
	this->addComponent(RenderComponent());
	this->addComponent(SpriteComponent());
	
	RenderComponent& renderComponent = this->getComponent<RenderComponent>();
	renderComponent.enabled = true;
	SpriteComponent& spriteComponent = this->getComponent<SpriteComponent>();
	
	//Sprite setup
	Resource_Manager& rm = Resource_Manager::getResourceManager();
	ResourceLoadingInfo rli;
	rli.name = "Casta";
	rli.type = "texture";
	rli.URL = "./casta.png";
	rm.loadResource(rli);
	spriteComponent.sprite.setTexture(rm.getTexture("Casta"));
	spriteComponent.sprite.setPosition(0, 0);
	sf::Vector2f targetSize(50, 50);
	sf::Vector2u size = spriteComponent.sprite.getTexture()->getSize();
	sf::Vector2f scale(targetSize.x / (float)size.x, targetSize.y / (float)size.y);
	spriteComponent.sprite.setScale(scale);

	// Then retrieve and use the ScriptComponent
	ScriptComponent& scriptComponent = this->getComponent<ScriptComponent>();
	// Assuming scriptComponent.script is a shared_ptr to DVDLogoBehaviour
	if (auto script = std::dynamic_pointer_cast<DVDLogoBehaviour>(scriptComponent.script)) {
		// Now 'script' is a shared_ptr to DVDLogoBehaviour, and you can use it
		script->sprite = &spriteComponent.sprite;
	}
}
Entity2D::Entity2D(entt::registry* registry, sf::Vector2f position):Entity2D(registry){
	SpriteComponent& spriteComponent = this->getComponent<SpriteComponent>();
	spriteComponent.sprite.setPosition(position);
}