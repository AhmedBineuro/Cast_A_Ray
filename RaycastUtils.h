#pragma once
#include "Map.h"
#include <SFMLMath.hpp>
namespace RaycastUtils {
	struct RayCollisionInfo {
		bool noHit=false;// True if the ray didn't collide with anything
		int side; // 0 for East/West or 1 for North/South
		int tag; // the block tag 
		double distance; // The raw distance to the collision point
		double perpindcularDistance; // The perpindicular distance [1/(Ray Direction in X or Y)]
		float u; // The u coordinate of the collision
	};
	RayCollisionInfo castRay(sf::Vector2f position, sf::Vector2f direction, Map m,float renderDistance=200.0f);

}