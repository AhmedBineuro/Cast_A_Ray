#include "Scene2D.h"
#include "Player.h"
#include "CameraRenderSystem.h"

// This is officially the scene for wolfenstien 3D style games!
class WolfScene :public Scene2D {
public:
	WolfScene();
	WolfScene(std::vector<std::string>mapNames);
	virtual void onCreate();
	virtual void onUpdate(float deltaTime);
	virtual void onFixedUpdate(float fixedDeltaTime);
	//Should return the canvas result as a sprite and is called every render call
	virtual sf::Sprite onRender();
	virtual void onDestroy();
	virtual void renderDebug(); // ImGui Debug Stuff
	virtual ~WolfScene();
	void changeMap(std::string mapName);
protected:
	PlayerController* playercontroller;
	CameraRenderSystem cameraRenderSystem;
	std::vector<Map> mapList;
	int currentMap;
	Player* player;
};