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
void DVDFactory(Scene2D& scene, sf::Vector2f location, sf::Vector2f size) {
    Resource_Manager& rm = Resource_Manager::getResourceManager();
    Entity* entity = scene.createEntity();
    entity->addComponent(RenderComponent());
    entity->addComponent(SpriteComponent());
    entity->addComponent(ScriptComponent(std::make_shared<DVDLogoBehaviour>()));

    ScriptComponent* script = entity->getComponent<ScriptComponent>();
    RenderComponent* render = entity->getComponent<RenderComponent>();
    SpriteComponent* sprite = entity->getComponent<SpriteComponent>();

    sprite->sprite.setTexture(rm.getTexture("DVD Logo"));
    sf::Vector2u textSize = sprite->sprite.getTexture()->getSize();
    sf::Vector2f newScale;
    newScale.x = size.x / (float)textSize.x;
    newScale.y = -size.y / (float)textSize.y;
    sprite->sprite.setScale(newScale);
    sprite->sprite.setPosition(location);
    DVDLogoBehaviour* behaviour = (DVDLogoBehaviour*)script->script.get();
    behaviour->spriteComponent = sprite;
    render->enabled = true;
}
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
    rli.name = "DVD Logo";
    rli.URL = "./dvdIcon.png";
    rm.loadResource(rli);
    Scene2D p1;
    ////////////////TESTING AREA/////////////////////
    for (int i = 0; i < 1; i++) {
        int xSize = 200;
        sf::Vector2f size(xSize, xSize/2);
        sf::Vector2f pos;
        pos.x = rand() / (float)RAND_MAX * ((float)WINDOW_WIDTH - size.x) + size.x;
        pos.y = rand() / (float)RAND_MAX * ((float)WINDOW_HEIGHT-size.y) + size.y;
        DVDFactory(p1, pos,size);
    }
    ///////////////////////////////////////////
    mainApp.addScene("Scene 2D", &p1);
    mainApp.run();
    return 0;
}


