#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Application.h"
#include "Entity.h"
#include "Camera.h"
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


class RandomSystem :public System {
public:
    void update(entt::registry& registry) {
        auto results = registry.view<TransformComponent>();
        std::cout << "In System\nAmount of Results: " << results.size() << std::endl;
        for (auto entity : results)
        {
            TransformComponent tf = results.get<TransformComponent>(entity);
            std::cout << tf.position.x << " " << tf.position.y << std::endl;
            std::cout << "DeltaTime: " <<globalDeltaTime<< std::endl;
        }
    }
};

//Test Scene class
class PlayGround :public Scene {
public:
    PlayGround() {
        l = Log();
        canvas.create(800, 800);
        l.setFontSize(24);
        l.setMargin(1);
        l.setSize(sf::Vector2f(400, 200));
        l.setBackgroundColor(sf::Color(90, 90, 140));
        systems.push_back(std::make_shared<RandomSystem>());
        entityList.push_back(std::move(std::make_unique<Entity>(&registry)));
        entityList.push_back(std::move(std::make_unique<Entity>(&registry)));
        entityList.push_back(std::move(std::make_unique<Camera>(&registry)));
        TransformComponent tf;
        tf.position = sf::Vector2f(20, 25);
        entityList[0]->addComponent(tf);
        onCreate();
    }
    void onCreate() {
        l.submit_message("OnCreate");
    };
    void onUpdate(float deltaTime) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && !QIsOn) {
            l.submit_message("Q is pressed", Warning);
            QIsOn = true;
            systems[0]->update(registry);
            switchScenes("AnotherScene");
        }
        else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) QIsOn = false;
    };
    void onFixedUpdate(float fixedDeltaTime) {
    };
    //Should return the canvas result as a sprite and is called every render call
    sf::Sprite onRender() {
        l.draw(canvas);
        canvasSprite.setTexture(canvas.getTexture());
        canvasSprite.setScale(1, -1);
        canvasSprite.setPosition(0, WINDOW_HEIGHT);
        return canvasSprite;
    };
    void onDestroy() {};
    Log l;
private:
    bool QIsOn = false;
    std::vector<std::unique_ptr<Entity>> entityList;
};
int main(){
    Application mainApp("PlayGround");
    MainApplication = &mainApp;
    mainApp.setWindowIcon("./cubelogo.png");
    PlayGround p1;
    mainApp.addScene("PlayGround", &p1);
    mainApp.run();
    return 0;
}


