#include "Scene2D.h"
#include "Player.h"
#include "CameraRenderSystem.h"
#include "MapColliderSystem.h"

// This is officially the scene for wolfenstien 3D style games!
class WolfScene :public Scene2D {
public:
	WolfScene();
	WolfScene(std::vector<std::string>mapNames);
	void onCreate();
	void onUpdate(float deltaTime);
	void onFixedUpdate(float fixedDeltaTime);
	//Should return the canvas result as a sprite and is called every render call
	sf::Sprite onRender();
	void onDestroy();
	void renderDebug(); // ImGui Debug Stuff
	~WolfScene();
	void changeMap(std::string mapName);
protected:
	PlayerController* playercontroller;
	TransformComponent* playerTransform;
	CameraRenderSystem cameraRenderSystem;
	MapColliderSystem mapColliderSystem;
	std::vector<Map> mapList;
	int currentMap;
	std::shared_ptr<Player> player;
};