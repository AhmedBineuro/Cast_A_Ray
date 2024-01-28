#include "Entity.h"
#include "Core.h"
#include "Actor.h"
//Entity2D behavior class
class DVDLogoBehaviour:public Actor {
public:
	DVDLogoBehaviour();
	void OnCreate()override;
	void OnUpdate(float deltaTime)override;
	void OnFixedUpdate(float fixedDeltaTime)override;
	void OnRender()override;
	void OnDestroy()override;
	void move(float deltaTime);
	~DVDLogoBehaviour();
	sf::Sprite* sprite;
	sf::Vector2f velocity;
};

class Entity2D:public Entity {
public:
	Entity2D(entt::registry* registry);
	Entity2D(entt::registry* registry,sf::Vector2f position);
};