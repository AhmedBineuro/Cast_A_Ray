#include "Application.h"
Application::Application() {
	this->appName = "Cast-A-Ray Application";
	Config& config = Config::getConfig();
	settings = config.getSettings();
	if (settings.antiAliasingLevel != antiAlias_values[currentAntiAlias]) {
		int size = sizeof(antiAlias_values) / sizeof(*antiAlias_values);
		for (int i = 0; i < size; i++)
		{
			if (antiAlias_values[i]==settings.antiAliasingLevel) {
				currentAntiAlias = i;
				break;
			}
		}
	}
	this->window.create(sf::VideoMode(settings.width, settings.height),this->appName, settings.fullscreen ? sf::Style::Fullscreen : sf::Style::Default,settings.videoSettings);
	this->canvas.create(400, 400);
	fixedDeltaTime = sf::seconds(0.5f);
	config.setFixedDeltaTime(0.5f);
	if (settings.capFrameRate) {
		window.setFramerateLimit(settings.maxFrameRate);
	}
	else {
		window.setFramerateLimit(0);
	}
	
	if (!icon.loadFromFile("./casta.png"))
		std::cout << "Failed to load window icon" << std::endl;
	else
		window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	FPS = 0;
	showFPS = false;
	this->sceneList.clear();
	this->canvasSprite.setPosition(0, 0);
}
Application::Application(std::string appName) {
	this->sceneList.clear();
	this->appName = appName;
	Config& config = Config::getConfig();
	settings = config.getSettings();
	if (settings.antiAliasingLevel != antiAlias_values[currentAntiAlias]) {
		int size = sizeof(antiAlias_labels) / sizeof(*antiAlias_labels);
		for (int i = 0; i < size; i++)
		{
			if (antiAlias_values[i] == settings.antiAliasingLevel) {
				currentAntiAlias = i;
				break;
			}
		}
	}
	this->window.create(sf::VideoMode(settings.width, settings.height), this->appName, settings.fullscreen ? sf::Style::Fullscreen : sf::Style::Default, settings.videoSettings);
	this->canvas.create(400, 400);
	fixedDeltaTime = sf::seconds(0.5f);
	config.setFixedDeltaTime(0.5f);
	if (settings.capFrameRate) {
		window.setFramerateLimit(settings.maxFrameRate);
	}
	else {
		window.setFramerateLimit(0);
	}
	
	if (!icon.loadFromFile("./casta.png"))
		std::cout << "Failed to load window icon" << std::endl;
	else
		window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	FPS = 0;
	showFPS = false;
	this->canvasSprite.setPosition(0, 0);
}
void Application::addScene(std::string name, Scene* scene) {
	if (currentScene == "")
		currentScene = name;
	sceneList[name] = scene;
}

bool Application::setCurrentScene(std::string name)
{
	if (sceneList.find(name) != sceneList.end()) {
		currentScene = name;
		return true;
	}
	return false;
}
void Application::removeScene(std::string name) {
	if (sceneList.find(name) != sceneList.end()) {
		sceneList.erase(name);
	}
}

void Application::setFixedDeltaTime(float fixedDeltaTime) {
	this->fixedDeltaTime = sf::seconds(fixedDeltaTime);
	Config& c = Config::getConfig();
	c.setFixedDeltaTime(fixedDeltaTime);
}

void Application::setWindowIcon(std::string URL) {
	sf::Image ico;
	if (!ico.loadFromFile(URL))
		std::cout << "Failed to load window icon" << std::endl;
	else
	{
		icon = ico;
		window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	}
}

void Application::setWindowIcon(sf::Image icon) {
	this->icon = icon;
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}


float Application::getFixedDeltaTime() {
	return fixedDeltaTime.asSeconds();
}

float Application::getDeltaTime() {
	return deltaTime.asSeconds();
}

void Application::run() {
	running = true;
	Config& config = Config::getConfig();
	ImGui::SFML::Init(window);
	float fixedDeltaTimeGUI = config.getFixedDeltaTime(); //For ImGui
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
	io.ConfigDockingWithShift = true;
	while (running) {
		if (config.RestartRequired()) {
			config.setRestartRequiredFlag(false);
			ImGui::SFML::Shutdown();
			restartWindow();
			ImGui::SFML::Init(window);
		}
		sf::Event event;
		bool scene_available = sceneList.find(currentScene) != sceneList.end();
		while (window.pollEvent(event)) {

			ImGui::SFML::ProcessEvent(event);
			if (scene_available)
			{
				sceneList[currentScene]->onEventLoop(event);
			}
			if (event.type == sf::Event::Closed)
			{
				window.close();
				running = false;
			}
			if (event.type == sf::Event::Resized)
			{
				window.setSize(sf::Vector2u(settings.width, settings.height));

				//canvas.create((unsigned int)(settings.width),(unsigned int)(settings.height));
			}
		}
		//////// CTRL+\ FOR SETTINGS
		bool keysArePressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Backslash) && (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::RControl));
		if (keysArePressed && (!keybindPressed))
		{
			keybindPressed = true;
			showSettings = !showSettings;
		}
		else if (!keysArePressed) {
			keybindPressed = false;
		}
		////////////////////////////////
		window.clear();
		canvas.clear();
		//window.draw(canvasSprite);
		ImGui::SFML::Update(window, deltaTime);
		//ImGui::SetNextWindowPos(ImVec2(0, 0));
		//ImGui::SetNextWindowSize(ImVec2(canvasSprite.getTexture()->getSize().x, canvasSprite.getTexture()->getSize().y));
		if(ImGui::BeginMainMenuBar()){
			if (ImGui::BeginMenu("File")) {
				ImGui::MenuItem("New Project");
				ImGui::MenuItem("Open Project");
				ImGui::MenuItem("Save Project");
				ImGui::MenuItem("Export");
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Edit")) {
				ImGui::MenuItem("Item1");
				ImGui::MenuItem("Item2");
				ImGui::MenuItem("Item3");
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("View")) {
				ImGui::MenuItem("Entity Properties");
				ImGui::MenuItem("Scene Properties");
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Preferences")) {
				ImGui::MenuItem("Show FPS");
				ImGui::MenuItem("Adjust window size");
				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}
		ImGui::Begin("##main_window");

		if(ImGui::BeginTabBar("Views##tab")) {
			if (ImGui::BeginTabItem("Viewport")){
				update();
				render(scene_available);
				ImGui::Image(canvasSprite);
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("Editor")) {
				ImGui::EndTabItem();
			}
			ImGui::EndTabBar();
		}
		ImGui::End();
		if(showSettings)
		{
			renderSettings(fixedDeltaTimeGUI, config);
		}
		ImGui::SFML::Render(window);
		window.display();
	}
	ImGui::SFML::Shutdown();
	window.close();
}
void Application::render(bool scene_available) {
	if (scene_available)
	{
		canvasSprite=sceneList[currentScene]->onRender();
		const sf::Texture* t = canvasSprite.getTexture();
		canvasSprite.setTextureRect(sf::IntRect(0, 0, t->getSize().x, t->getSize().y));
		canvas.draw(canvasSprite);
		//canvasSprite.setTexture(canvas.getTexture());
	}
}
void Application::renderSettings(float &fixedDeltaTimeGUI,Config& config) {
	// This is all just to render the settings widget//
	ImGui::Begin("Settings");
	if (showFPS) {
		ImGui::Text((std::string("FPS: ") + std::to_string(FPS)).c_str());
	}
	ImGui::Checkbox("Fullscreen", &(settings.fullscreen));
	ImGui::Checkbox("Vsync", &(settings.vsync));
	ImGui::Checkbox("Limit frame rate", &(settings.capFrameRate));
	ImGui::Checkbox("Show FPS", &(this->showFPS));
	if (settings.capFrameRate)
		ImGui::InputInt("Max frame rate", &settings.maxFrameRate);
	int tempArray[2] = { settings.width,settings.height };
	if (ImGui::InputInt2("Window dimensions", tempArray)) {
		settings.width = tempArray[0];
		settings.height = tempArray[1];
	}
	int tempArray2[2] = { settings.renderResolution.x,settings.renderResolution.y};
	if (ImGui::InputInt2("Render Resolution", tempArray2)) {
		settings.renderResolution.x = tempArray2[0];
		settings.renderResolution.y = tempArray2[1];
	}
	ImGui::InputFloat("Fixed delta time", &fixedDeltaTimeGUI, 0.05);
	ImGui::Combo("Anti-Aliasing level", &currentAntiAlias, antiAlias_labels, sizeof(antiAlias_labels) / sizeof(*antiAlias_labels));
	settings.antiAliasingLevel = antiAlias_values[currentAntiAlias];
	ImGui::Checkbox("Show Scene Debug Window", &(showSceneDebug));
	if (ImGui::Button("Apply settings")) {
	config.setSettings(settings);
	config.applyChanges();
	//Detect Resize Update
	sf::Vector2u internalDimensions = config.getDimensions();
	if (internalDimensions != window.getSize())
	{
		window.setSize(internalDimensions);
	}
	if (settings.capFrameRate)
		window.setFramerateLimit(settings.maxFrameRate);
	else
		window.setFramerateLimit(0);
	if (config.getDeltaTime() != fixedDeltaTimeGUI) {
		config.setDeltaTime(fixedDeltaTimeGUI);
		this->fixedDeltaTime = sf::seconds(fixedDeltaTimeGUI);
	}
	this->canvas.create(settings.renderResolution.x, settings.renderResolution.y);
	}
	ImGui::End();
	if(showSceneDebug)
	{
		this->sceneList[currentScene]->renderImGui();
	}
}

void Application::update() {
	Config& config = Config::getConfig();
	deltaTime = clock.restart();
	config.setDeltaTime(deltaTime.asSeconds());
	cumulatedTime += deltaTime;
	while (cumulatedTime >= fixedDeltaTime){
		//Check if the show FPS flag is on and if it is,show it
		if (showFPS) {
			FPS = 1.0f / deltaTime.asSeconds();
			window.setTitle(appName + " | FPS: " + std::to_string((int)FPS));
		}
		else window.setTitle(appName);
		cumulatedTime -= fixedDeltaTime;
		//Update scene fixed delta time systems;
		if (sceneList.find(currentScene) != sceneList.end())
			if (ImGui::IsWindowFocused())
				sceneList[currentScene]->onFixedUpdate(fixedDeltaTime.asSeconds());
	}
	//Update scene delta time systems;
	if (sceneList.find(currentScene) != sceneList.end())
		if (ImGui::IsWindowFocused())
			sceneList[currentScene]->onUpdate(deltaTime.asSeconds());
}

//Function will restart the window to apply the necessary settings changes
void Application::restartWindow() {
	window.close();
	Config& config = Config::getConfig();
	this->window.create(sf::VideoMode(settings.width, settings.height), this->appName, settings.fullscreen ? sf::Style::Fullscreen : sf::Style::Default, settings.videoSettings);
	settings.width = window.getSize().x;
	settings.height = window.getSize().y;
	if (settings.capFrameRate)
		window.setFramerateLimit(settings.maxFrameRate);
	else
		window.setFramerateLimit(0);
	window.clear();
	window.draw(sceneList[currentScene]->onRender());
	render(sceneList.find(currentScene) != sceneList.end());
}