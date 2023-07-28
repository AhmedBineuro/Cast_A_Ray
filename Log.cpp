#include"Log.h"
sf::Font font;
Log::Log()
{
    m_message_history = std::vector<std::string>(0);
    m_formatted_text = std::vector<std::string>(0);
    if (!font.loadFromFile("./CourierPrime-Regular.ttf"))
    {
        std::cout << "Couldn't load font" << std::endl;
    }
    m_currentLine.setFont(font);
    m_background = sf::RectangleShape();
    m_background.setSize(sf::Vector2f(200, 200));
    m_background.setFillColor(sf::Color::Black);
    m_fontSize = 12;
    m_currentLine.setCharacterSize(m_fontSize);
    m_currentLine.setFillColor(sf::Color::Green);
    refreshFontAttributes();
    updateBounds();
}
void Log::draw(sf::RenderTarget& renderTarget, sf::RenderStates states)
{
    renderTarget.draw(m_background);
    int cursor_position = m_margin;
    sf::Vector2f position = m_background.getPosition();
    for (std::string line : m_formatted_text)
    {
        float x = position.x + m_margin * m_single_char_width;
        float y = position.y + (cursor_position) * (m_fontSize);
        m_currentLine.setString(line);
        m_currentLine.setPosition(x, y);
        renderTarget.draw(m_currentLine);
        cursor_position++;
    }
}
void Log::setFont(sf::Font& font)
{
    m_currentLine.setFont(font);
    refreshFontAttributes();
}
void Log::setTextColor(sf::Color new_color)
{
    m_currentLine.setFillColor(new_color);
}
void Log::setBackgroundColor(sf::Color new_color)
{
    m_background.setFillColor(new_color);
}
void Log::setMargin(int margin)
{
    m_margin = margin;
    updateBounds();
}
void Log::setFontSize(int fontSize)
{
    m_fontSize = fontSize;
    m_currentLine.setCharacterSize(fontSize);
    refreshFontAttributes();
};
void Log::refreshFontAttributes()
{
    sf::Text singleChar = m_currentLine;
    singleChar.setString("X");
    int width = singleChar.getGlobalBounds().width;
    m_single_char_width = width;
    std::cout << "Success" << std::endl;
    updateBounds();
}
void Log::setSize(sf::Vector2f size)
{
    m_background.setSize(size);
    updateBounds();
    refreshFormattedText();
}
void Log::setPosition(sf::Vector2f position)
{
    m_background.setPosition(position);
}

void Log::submit_message(std::string message)
{
    m_message_history.push_back(message);
    for (std::string line : wrapTextVectorized(message))
    {
        // Pop the top of the vector to move the view down by one line adding the new line will cause an overflow
        if ((m_formatted_text.size() + 1) > m_max_char_count.y)
            m_formatted_text.erase(m_formatted_text.begin());
        m_formatted_text.push_back(line);
    }
}

std::vector<std::string> Log::getWords(std::string str)
{
    std::vector<std::string> output(0);
    std::string currentWord = "";
    for (char c : str)
    {
        if (!isspace(c))
            currentWord += c;
        else
        {
            output.push_back(currentWord);
            currentWord = "";
        }
    }
    if (currentWord != "")
        output.push_back(currentWord);
    return output;
}
std::string Log::wrapText(std::string str)
{
    std::vector<std::string> parsed = getWords(str);
    int currentCharCount = 0;
    std::string output = "";
    for (std::string word : parsed)
    {
        if (currentCharCount + word.length() > m_max_char_count.x)
        {
            output += "\n";
            currentCharCount = 0;
        }
        if (word.length() <= m_max_char_count.x)
        {
            output += word + " ";
            currentCharCount += word.length() + 1;
        }
        else
        {
            for (int i = 0; i <= ceil(word.length() / m_max_char_count.x); i++)
            {
                std::string half = word.substr(i * m_max_char_count.x, m_max_char_count.x);
                output += half + "\n";
            }
        }
    }
    return output;
}

std::vector<std::string> Log::wrapTextVectorized(std::string str)
{
    std::vector<std::string> parsed = getWords(str);
    int currentCharCount = 0;
    std::string currentLine = "";
    std::vector<std::string> output(0);
    for (std::string word : parsed)
    {
        if (currentCharCount + word.length() > m_max_char_count.x)
        {
            output.push_back(currentLine);
            currentLine = "";
            currentCharCount = 0;
        }
        if (word.length() <= m_max_char_count.x)
        {
            currentLine += word + " ";
            currentCharCount += word.length() + 1;
        }
        else
        {
            for (int i = 0; i <= ceil(word.length() / m_max_char_count.x); i++)
            {
                std::string half = word.substr(i * m_max_char_count.x, m_max_char_count.x);
                output.push_back(half);
            }
        }
    }
    if (currentLine != "")
        output.push_back(currentLine);
    return output;
}
void Log::updateBounds()
{
    int width = m_background.getSize().x;
    int height = m_background.getSize().y;
    m_max_char_count.x = width / m_single_char_width - (m_margin * 2);
    m_max_char_count.y = height / (m_fontSize)-(m_margin * 2);
}
void Log::refreshFormattedText()
{
    m_formatted_text.clear();

    for (std::string message : m_message_history)
    {
        for (std::string line : wrapTextVectorized(message))
        {
            // Pop the top of the vector to move the view down by one line adding the new line will cause an overflow
            if ((m_formatted_text.size() + 1) > m_max_char_count.y)
                m_formatted_text.erase(m_formatted_text.begin());
            m_formatted_text.push_back(line);
        }
    }
}