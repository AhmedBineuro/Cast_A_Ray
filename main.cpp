#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Map_Reader.h"
/**
* @todo create a resource manager so the engine doesn't load the same texture or
* sound multiple times. The resource manager will be a 3 maps of name and resource. The three
* maps will be for texture, sound, and debug color.
* @todo create an entity manager that will just map an entity name to a specific class.
* An entity is can be an enemy, a sprite, or a billboard.
*/
int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    Map_Reader& m=Map_Reader::getReader();
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
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}