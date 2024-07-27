#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Application.h"
#include "DDAScene.h"
//For Release WINDOWS
//#include <windows.h>
Application *MainApplication;
bool switchScenes(std::string sceneName) {
    if (MainApplication != nullptr){
        return MainApplication->setCurrentScene(sceneName);
    }
    return false;
}

//For Debug
int main(){
    srand(time(NULL));
    Application mainApp("PlayGround");
    MainApplication = &mainApp;
    mainApp.setWindowIcon("./cubelogo.png");
    Resource_Manager& rm = Resource_Manager::getResourceManager();
    ResourceLoadingInfo rli;
    rli.name = "Casta";
    rli.type = "texture";
    rli.URL = "./casta.png";
    rm.loadResource(rli);
    rli.name = "PlayerSprite";
    rli.URL = "./Player.png";
    rm.loadResource(rli);
    DDAScene p1("PlayGround");
    mainApp.addScene("WolfScene", &p1);
    mainApp.run();
    return 0;
}
//For Release WINDOWS

//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
//    srand(time(NULL));
//    Application mainApp("PlayGround");
//    MainApplication = &mainApp;
//    mainApp.setWindowIcon("./cubelogo.png");
//    Resource_Manager& rm = Resource_Manager::getResourceManager();
//    ResourceLoadingInfo rli;
//    rli.name = "Casta";
//    rli.type = "texture";
//    rli.URL = "./casta.png";
//    rm.loadResource(rli);
//    rli.name = "PlayerSprite";
//    rli.URL = "./Player.png";
//    rm.loadResource(rli);
//    DDAScene p1("PlayGround");
//    mainApp.addScene("WolfScene", &p1);
//    mainApp.run();
//    return 0;
//}


