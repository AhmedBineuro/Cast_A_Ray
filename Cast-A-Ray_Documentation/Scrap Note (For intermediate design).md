## Scene Class
- The scene is basically a screen of the game 
- Basic Scene
```C++
class Scene{
public:
Scene();
void onUpdate(float deltaTime); //For the user defined delta time (parameter called in game class)
void onFixedUpdate(float deltaTime); //Delta time set at 60 fps
void onRender(sf::RenderTexture& screen); // TBD whether to implement or not
void onDestroy(); // TBD whether to implement or not
private:
entt::registry registry;
std::vector<std::vector<int>> levelLayout;
std::vector<std::shared_ptr<GUI_Element> GUI;
std::string name;
int buildOrder;
}
```
## GUI_Element class
```C++
class GUI_Element{
public:
GUI_Element();
bool isHighlighted(sf::Vector2f position);
void onClick();
private:
sf::FloatRect border;
sf::Sprite sprite;
}
```