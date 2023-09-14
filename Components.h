#pragma once
#include"SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFMLMath.hpp"
#include <math.h>
#include "Log.h"
#include "single_include/entt/entt.hpp"
sf::Vector2f calculatePlane(sf::Vector3f dir,int fov) {
	sf::Vector2f plane = sf::Vector2f();
	sf::rotate(plane, fov);
	float width = (float)tan(fov / 2);
	sf::normalize(plane);
	plane *= width;
	return plane;
}
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
	bool active;
	sf::RenderTarget* target;
	sf::RenderStates* states;
	drawable_component(sf::RenderTarget &surface, bool activeState) {
		target = &surface;
		states = nullptr;
		active = activeState;
	}
	drawable_component(sf::RenderTarget& surface, sf::RenderStates& state,bool activeState) {
		target = &surface;
		states = &state;
		active = activeState;
	}
	drawable_component(sf::RenderTarget& surface, sf::RenderStates& state,bool activeState) {
		target = &surface;
		states = &state;
		active = activeState;
	}
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
	life_component() : current_health(10),max_health(10) {}
	life_component(int initialhealth,int maxhealth) :current_health(initialhealth), max_health(maxhealth) {}
};
struct logger_component {
	std::vector<Message> message_log;
	int log_ID;
	logger_component() :log_ID(-1) {}
	logger_component(int log_ID) :log_ID(log_ID) {}
};
struct map_tag_component {
	std::string map_name;
	int map_id;
	map_tag_component() :map_name("None"), map_id(-1) {}
	map_tag_component(std::string name, int id) :map_name(name),map_id(id){}
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
	float render_distance=50;
	sf::Vector2f plane=sf::Vector2f(1,0);
	sf::VertexArray rays;
	perspective_component() :direction(sf::Vector3f(0, 1, 0)),FOV(90),render_distance(50){
		plane = calculatePlane(sf::Vector3f(0, 1, 0), 90);
	}
	perspective_component(sf::Vector3f dir, int fov, float render_distance) : direction(dir), FOV(fov), render_distance(render_distance){
		plane = calculatePlane(dir, fov);
	}
};
struct player_id_component {
	int id;
	player_id_component() :id(1){}
	player_id_component(int id) :id(id) {}
};
struct position_component {
	sf::Vector3f literal_position;
	position_component() : literal_position(sf::Vector3f()) {}
	position_component(sf::Vector3f position) : literal_position(position) {}
};
struct sprite_component {
	sf::Sprite sprite;
	sprite_component(sf::Sprite sprite) : sprite(sprite) {}
};