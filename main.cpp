#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Map_Reader.h"
#include "Log.h"
#include <iostream>
#include <thread>
bool run = true;
Log l;
sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");
void checkForInput() {
    while (window.isOpen()) {
        std::string input;
        std::cout << "Enter a sentence to parse into words" << std::endl;
        std::getline(std::cin, input);
        l.submit_message(input);
    }
}

int main()
{
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    Map_Reader m;
    l.setBackgroundColor(sf::Color(255,255,255,150));
    l.setTextColor(sf::Color::Yellow);
    l.setPosition(sf::Vector2f(300, 300));
    l.setFontSize(10);
    l.setMargin(1);
    l.setSize(sf::Vector2f(600, 200));
    //std::cout << "Success" << std::endl;
    m.processLevel("test.car");
    /**
    * @todo Change the icon both in the resource and here to your own icon + include the png in the release file after building for sfml icon  
    */
    sf::Image icon;
    for(Segment segment: m.getAllSegments())
    {
        printSegment(segment);
        std::cout << std::endl;
    }
    if(!icon.loadFromFile("./casta.png"))
        std::cout<<"Failed to load window icon"<<std::endl;
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    m.processLayoutInfo();
    std::thread inputThread(checkForInput);
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
        window.draw(shape);
        l.draw(window,sf::RenderStates());
        window.display();
        
    }
    inputThread.join();
    return 0;
}