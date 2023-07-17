#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <iostream>
/**
* @brief A class that displays a log of any engine related events to allow in engine debugging.
* Any engine component will be able to link to a Log object. When linked the component
* will post any errors and messages to the log instead of the console window.  
*/
class Log {
public:
	Log();

	/**
	* @brief Function to get sll the messages in log as a string
	* @note this is mostly used to debug the Log object and test its behaviour.
	* @return The full log as a string
	*/
	std::string stringifyFull();
	/**
	* @brief Function to get the messages log vector
	* @note this is mostly used to debug the Log object and test its behaviour.
	* @return A vector of log messages
	*/
	std::vector<std::string>getFullLog();
	/**
	* @brief Function to set the dimensions of the log
	* @note The dimensions mentioned here refer to the pixel size and not the character count per line
	*/
	void setDimensions(sf::Vector2f dimensions);
	/**
	* @brief Function to set the position of the log
	*/
	void setPosition(sf::Vector2f dimensions);
	/**
	* @brief Function to clear the message log vector
	*/
	void clearHistory();
private:
	std::vector<std::string> messageLog;
	sf::Vector2f dimensions;
	sf::RectangleShape background;
};