#include"Log.h"
Log::Log()
{
    m_message_history = std::vector<Message>(0);
    m_in_view_messages = std::vector<In_view_message>(0);
    Resource_Manager& rm = Resource_Manager::getResourceManager();
    m_currentLine.setFont(rm.getFont("DEF_LOG"));
    m_background = sf::RectangleShape();
    m_background.setSize(sf::Vector2f(200, 200));
    m_background.setFillColor(sf::Color::Black);
    m_fontSize = 12;
    m_currentLine.setCharacterSize(m_fontSize);
    m_priority_color[0] = sf::Color(0, 128,255);
    m_priority_color[1] = sf::Color(127, 0, 255);
    m_priority_color[2] = sf::Color(255, 0, 255);
    m_priority_color[3] = sf::Color(255, 0, 127);
    m_currentLine.setFillColor(sf::Color::Green);
    refreshFontAttributes();
    updateBounds();
}
void Log::draw(sf::RenderTarget& renderTarget)
{
    renderTarget.draw(m_background);
    int cursor_position = m_margin;
    sf::Vector2f position = m_background.getPosition();
    for (In_view_message message : m_in_view_messages)
    {
        float x = position.x + m_margin * m_single_char_width;
        float y = position.y + (cursor_position) * (m_fontSize);
        m_currentLine.setString(message.message_contents);
        m_currentLine.setPosition(x, y);
        m_currentLine.setFillColor(m_priority_color[message.priority]);
        renderTarget.draw(m_currentLine);
        cursor_position++;
    }
}
void Log::draw(sf::RenderTarget& renderTarget, sf::RenderStates states)
{
    renderTarget.draw(m_background,states);
    int cursor_position = m_margin;
    sf::Vector2f position = m_background.getPosition();
    for (In_view_message message : m_in_view_messages)
    {
            float x = position.x + m_margin * m_single_char_width;
            float y = position.y + (cursor_position) * (m_fontSize);
            m_currentLine.setString(message.message_contents);
            m_currentLine.setPosition(x, y);
            m_currentLine.setFillColor(m_priority_color[message.priority]);
            renderTarget.draw(m_currentLine,states);
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
    int width = (int)singleChar.getGlobalBounds().width;
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
    Message new_message;
    new_message.priority = Low;
    new_message.message_contents = message;
    new_message.formatted_message = wrapTextVectorized(message);
    m_message_history.push_back(new_message);
    for (std::string line : new_message.formatted_message)
    {
        // Pop the top of the vector to move the view down by one line adding the new line will cause an overflow
        if ((m_in_view_messages.size() + 1) > m_max_char_count.y)
            m_in_view_messages.erase(m_in_view_messages.begin());
        m_in_view_messages.push_back(In_view_message{new_message.priority,line});
    }
    
    
    //for (std::string line : wrapTextVectorized(message))
    //{
    //    // Pop the top of the vector to move the view down by one line adding the new line will cause an overflow
    //    if ((m_in_view_messages.size() + 1) > m_max_char_count.y)
    //        m_in_view_messages.erase(m_in_view_messages.begin());
    //    m_in_view_messages.push_back();
    //}
}

void Log::submit_message(std::string message,enum Priority priority)
{
    Message new_message;
    new_message.priority = priority;
    new_message.message_contents = message;
    new_message.formatted_message = wrapTextVectorized(message);
    m_message_history.push_back(new_message);
    for (std::string line : new_message.formatted_message)
    {
        // Pop the top of the vector to move the view down by one line adding the new line will cause an overflow
        if ((m_in_view_messages.size() + 1) > m_max_char_count.y)
            m_in_view_messages.erase(m_in_view_messages.begin());
        m_in_view_messages.push_back(In_view_message{ new_message.priority,line });
    }
    //m_message_history.push_back(message);
    //for (std::string line : wrapTextVectorized(message))
    //{
    //    // Pop the top of the vector to move the view down by one line adding the new line will cause an overflow
    //    if ((m_in_view_messages.size() + 1) > m_max_char_count.y)
    //        m_in_view_messages.erase(m_in_view_messages.begin());
    //    m_in_view_messages.push_back(line);
    //}
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
            currentCharCount += (int)word.length() + 1;
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
            currentCharCount += (int)word.length() + 1;
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
    int width = (int)m_background.getSize().x;
    int height = (int)m_background.getSize().y;
    m_max_char_count.x = width / m_single_char_width - (m_margin * 2);
    m_max_char_count.y = height / (m_fontSize)-(m_margin * 2);
}
void Log::refreshFormattedText()
{
    for (Message message : m_message_history)
    {
        message.formatted_message = wrapTextVectorized(message.message_contents);
        //for (std::string line : wrapTextVectorized(message))
        //{
        //    // Pop the top of the vector to move the view down by one line adding the new line will cause an overflow
        //    if ((m_in_view_messages.size() + 1) > m_max_char_count.y)
        //        m_in_view_messages.erase(m_in_view_messages.begin());
        //    m_in_view_messages.push_back(line);
        //}
    }
}