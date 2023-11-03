#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Map_Reader.h"
#include "Log.h"
#include "Resource_Manager.h"
#include "Camera.h"
#include <iostream>
#include <thread>
#include "imgui.h"
#include "imgui-SFML.h"
void windowLoop();
void window2Loop();
static bool run = true;
Log l;
Camera c;
Map_Reader& m=m.getReader();
int priority = 0;
const char* priority_list[] = { "Low", "Medium", "High", "Warning"};
const int bufferSize = 2048;
static char buffer[bufferSize] = "";
int main(){
    l.setBackgroundColor(sf::Color(255,255,255,150));
    l.setTextColor(sf::Color::Yellow);
    l.setPosition(sf::Vector2f(200, 400));
    l.setFontSize(15);
    l.setMargin(1);
    l.setSize(sf::Vector2f(600, 200));
    //std::cout << "Success" << std::endl;
    m.processLevel("test.car");

    for(Segment segment: m.getAllSegments())
    {
        printSegment(segment);
        std::cout << std::endl;
    }
    m.processLayoutInfo();
    std::thread windowThread(windowLoop);
    std::thread window2Thread(window2Loop);
    windowThread.join();
    window2Thread.join();
    return 0;
}

void windowLoop() {
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Cast-A-Ray");
    sf::Clock deltaClock;
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
void window2Loop() {
    sf::RenderWindow window(sf::VideoMode(400, 400), "Debug");
    sf::Clock deltaClock;
    ImGui::SFML::Init(window);
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
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed)
            {
                window.close();
                run = false;
            }
        }
        ImGui::SFML::Update(window, deltaClock.restart());
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImVec2(400, 400));
        //SFML ImGUI test
        ImGui::Begin("Window title");
        ImGui::Text("Some Text");
        ImGui::Combo("Priority:", &priority, priority_list, IM_ARRAYSIZE(priority_list));
        ImGui::InputText("Log message", buffer, bufferSize);
        if (ImGui::Button("Submit Message")) {
            l.submit_message(std::string(buffer), static_cast<Priority>(priority));
        }
        ImGui::End();
        window.clear();
        ImGui::SFML::Render(window);

        window.display();
    }
    ImGui::SFML::Shutdown();
}