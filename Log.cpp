#include "Log.h"
Log::Log() {
	this->messageLog = std::vector<std::string>(0);
	this->dimensions = sf::Vector2f(100, 100);
	this->background = sf::RectangleShape();
	this->background.setSize(this->dimensions);
	this->background.setFillColor(sf::Color(0, 0, 0, 150));
}
std::string Log::stringifyFull() {
    std::string output = "";
    if (!this->messageLog.empty())
    {
        for (int i = 0; i < this->messageLog.size(); i++)
        {
            output += "- " + this->messageLog[i] + "\n";
        }
    }
    return output;
}