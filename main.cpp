#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Application.h"
#include "Scenes.h"
#include "CoreAdditions.h"
#include "WolfScene.h"
#include <iostream>
Application *MainApplication;
bool switchScenes(std::string sceneName) {
    if (MainApplication != nullptr){
        return MainApplication->setCurrentScene(sceneName);
    }
    return false;
}

/* 
* So I discovered after making this whole design of Scenes, entities, and Game I
* made a general SFML application framework. So Now onto the to-do's
* @TODO
*   - [X] Make Systems for RayCaster 
*   - [ ] Make Separate Cast-A-Ray library such that
*       - [ ] Empty Components file (Special for each project)
*       - [ ] And just the main function (To add the scenes and other stuff)
*/
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
    WolfScene p1({"PlayGround"});
    mainApp.addScene("WolfScene", &p1);
    mainApp.run();
    return 0;
}


