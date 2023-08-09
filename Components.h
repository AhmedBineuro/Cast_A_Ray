#pragma once
#include"SFML/Graphics.hpp"
#include "single_include/entt/entt.hpp"
struct position_component {
	sf::Vector3f value;
};
struct velocity_component {
	sf::Vector3f value;
};
struct direction_component {
	sf::Vector3f value;
};
struct raycaster_component {
	int FOV;
	int render_distance;
	sf::Vector3f direction;
};
struct health_component {
	int value;
};
struct tag_component {
	int value;
};
struct sprite_component {
	sf::Sprite value;
};