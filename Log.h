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
public:
    Log();
    void draw(sf::RenderTarget& renderTarget, sf::RenderStates states);
    void setFont(sf::Font& font);
    void setTextColor(sf::Color new_color);
    void setBackgroundColor(sf::Color new_color);
    /**
    * @@param margin the margin in characters
    */
    void setMargin(int margin);
    void setFontSize(int fontSize);
    void refreshFontAttributes();
    void setSize(sf::Vector2f size);
    void setPosition(sf::Vector2f position);

    /**
     * @brief Function to submit a message into the text box
     */
    void submit_message(std::string message);

private:
    std::vector<std::string> m_message_history;
    std::vector<std::string> m_formatted_text;
    sf::RectangleShape m_background;
    sf::Text m_currentLine;
    int m_margin, m_fontSize, m_single_char_width;
    /**
     * @brief Describes the max count of characters in the text box (horizontal and vertical)
     */
    sf::Vector2i m_max_char_count;

    /**
     * @brief Function to fetch the words in a sentence
     * @returns Vector of words
     */

    std::vector<std::string> getWords(std::string str);
    /**
     * @brief Function to perform text wrapping according to a specififc character count
     * @returns String with the wrapping performed using new line characters
     */
    std::string wrapText(std::string str);

    /**
     * @brief Function to perform text wrapping according to a specififc character count
     * @returns Vector of strings where each line is a string
     */
    std::vector<std::string> wrapTextVectorized(std::string str);
    /**
     * @brief Function to update the max character count horizontally and vertically in the view
     */
    void updateBounds();
    /**
    * @brief Function to reformat the text in the log
    */
    void refreshFormattedText();
};