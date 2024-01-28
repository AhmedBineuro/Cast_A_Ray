#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Application.h"
#include "Scenes.h"
#include <iostream>
Application *MainApplication;
void switchScenes(std::string sceneName) {
    if (MainApplication != nullptr)
        MainApplication->setCurrentScene(sceneName);
}

/* 
* So I discovered after making this whole design of Scenes, entities, and Game I
* made a general SFML application framework. So Now onto the to-do's
* @TODO
*   - [ ] Make Systems for RayCaster 
*   - [ ] Make Separate Cast-A-Ray library such that
*       - [ ] Empty Components file (Special for each project)
*       - [ ] And just the main function (To add the scenes and other stuff)
*/

int main(){
    srand(time(NULL));
    Application mainApp("PlayGround");
    MainApplication = &mainApp;
    mainApp.setWindowIcon("./cubelogo.png");
    Scene2D p1;
    mainApp.addScene("Scene 2D", &p1);
    mainApp.run();
    return 0;
}


