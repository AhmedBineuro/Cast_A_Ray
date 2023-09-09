#pragma once
#include"SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFMLMath.hpp"
#include "Log.h"
#include "single_include/entt/entt.hpp"
struct animator_component {
	sf::IntRect frame;
	sf::Vector2i current_frame;
	sf::Vector2i dimensions;
};
struct audio_emmiter_component {
	std::shared_ptr<sf::Sound> sound;
	bool active;
	bool spacial;
};
struct audio_listener_component {
	std::shared_ptr<sf::Listener> sound;
};
struct collider_component {
	std::shared_ptr<sf::Sprite> sprite;
	sf::IntRect bounds;
};
struct drawable_component {
	sf::RenderTarget& target;
	sf::RenderStates& states;
};
struct entity_id_component {
	int id;
};
struct input_component {
	sf::RenderWindow& window;
	bool active;
};
struct life_component {
	int current_health;
	int max_health;
	life_component(int initialhealth,int maxhealth) :current_health(initialhealth), max_health(maxhealth) {}
};
struct logger_component {
	std::vector<Message> message_log;
	int log_ID;
	logger_component(int log_ID) :log_ID(log_ID);
};
struct map_tag_component {
	std::string map_name;
	int map_id;
};

struct move_component {
	sf::Vector3f velocity;
	sf::Vector3f acceleration;
	float friction;
	float max_speed;
};
struct perspective_component {
	sf::Vector3f direction=sf::Vector3f(0,1,1);
	int FOV=90;
	float max_view_distance=50;
	sf::Vector2f plane=sf::Vector2f(1,0);
	sf::VertexArray rays;
	perspective_component(sf::Vector3f dir,int fov, float max_view_distance, sf::Vector3f plane)
};
struct player_id_component {
	int id;
	player_id_component(int id) :id(id) {}
};
struct position_component {
	sf::Vector3f literal_position;
	sf::Vector3i grid_position;
};
struct sprite_component {
	sf::Sprite sprite;
};