#pragma once
#include <math.h>
#include <memory>
#include"SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFMLMath.hpp"
#include "Log.h"
#include "entt.hpp"
sf::Vector2f calculatePlane(sf::Vector3f dir, int fov);
struct animator_component {
	sf::IntRect frame;
	sf::Vector2i current_frame;
	sf::Vector2i dimensions;
};
struct transform_component {
	sf::Vector3f position,rotation;
	transform_component() : position(sf::Vector3f()),rotation(sf::Vector3f()) {}
	transform_component(sf::Vector3f position) : position(position) {}
	transform_component(sf::Vector3f position, sf::Vector3f rotation) : position(position), rotation(rotation) {}
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
	sf::RenderTexture *target;
	std::shared_ptr<sf::RenderStates> states;
	drawable_component(sf::RenderTexture &surface, bool activeState) {
		target = &surface;
		states = nullptr;
		active = activeState;
	}
	drawable_component(sf::RenderTexture& surface) {
		target = &surface;
		states = nullptr;
		active = false;
	}
	drawable_component(sf::RenderTexture& surface, sf::RenderStates& state,bool activeState) {
		target = &surface;
		states = std::make_shared<sf::RenderStates>(state);
		active = activeState;
	}
};
struct entity_id_component {
	int id;
};
// @todo Instead of doing this maybe just use the sfml event loop manually 
// @note You don't have to cater to literally everyone
//struct input_component {
//	sf::RenderWindow& window;
//	bool active;
//};
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
	sf::Vector3f direction;
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
struct sprite_component {
	sf::Sprite sprite;
	sprite_component(sf::Sprite sprite) : sprite(sprite) {}
};