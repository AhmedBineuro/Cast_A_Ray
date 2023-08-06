#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Map_Reader.h"
#include "Log.h"
#include "Resource_Manager.h"
#include "SFMLMath.hpp"
#include <iostream>
#include <thread>
static bool run = true;
Log l;
Map_Reader& m=m.getReader();
void checkForInput() {
    std::cout << "Enter a sentence to parse into words" << std::endl;
    while (run) {
        std::string input;
        std::getline(std::cin, input);
        l.submit_message(input);
    }
}
void windowLoop() {
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");
    Resource_Manager& r = Resource_Manager::getResourceManager();
    sf::Image icon;
    if (!icon.loadFromFile("./casta.png"))
    std::cout << "Failed to load window icon" << std::endl;
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    while (run)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                run = false;
            }
        }
        window.clear();
        l.draw(window);
        window.display();
    }
}

int main(){
    l.setBackgroundColor(sf::Color(255,255,255,150));
    l.setTextColor(sf::Color::Yellow);
    l.setPosition(sf::Vector2f(300, 300));
    l.setFontSize(20);
    l.setMargin(4);
    l.setSize(sf::Vector2f(600, 200));
    //std::cout << "Success" << std::endl;
    m.processLevel("test.car");

    //for(Segment segment: m.getAllSegments())
    //{
    //    printSegment(segment);
    //    std::cout << std::endl;
    //}
    m.processLayoutInfo();
    std::thread windowThread(windowLoop);
    std::thread inputThread(checkForInput);
    inputThread.join();
    windowThread.join();

    return 0;
}