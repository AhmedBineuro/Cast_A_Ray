#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Application.h"
#include "Scenes.h"
#include "CoreAdditions.h"
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
    Resource_Manager& rm = Resource_Manager::getResourceManager();
    ResourceLoadingInfo rli;
    rli.name = "Casta";
    rli.type = "texture";
    rli.URL = "./casta.png";
    rm.loadResource(rli);
    Scene2D p1;
    ////////////////TESTING AREA/////////////////////
    Entity* dvd = p1.createEntity();
    dvd->addComponent(RenderComponent());
    dvd->addComponent(SpriteComponent());
    dvd->addComponent(ScriptComponent(std::make_shared<DVDLogoBehaviour>()));
    
    ScriptComponent* script = dvd->getComponent<ScriptComponent>();
    RenderComponent* render = dvd->getComponent<RenderComponent>();
    SpriteComponent* sprite = dvd->getComponent<SpriteComponent>();
    
    sprite->sprite.setTexture(rm.getTexture("Casta"));
    sprite->sprite.setScale(sf::Vector2f(0.2f, 0.2f));
    sprite->sprite.setPosition(200, 200);
    DVDLogoBehaviour* behaviour = (DVDLogoBehaviour*)script->script.get();
    behaviour->spriteComponent = sprite;
    render->enabled = true;
    ///////////////////////////////////////////
    mainApp.addScene("Scene 2D", &p1);
    mainApp.run();
    return 0;
}


