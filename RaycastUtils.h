#pragma once
namespace RaycastUtils {
	struct rayCollisionInfo {
		bool noHit;// True if the ray didn't collide with anything
		int side; // 0 for East/West or 1 for North/South
		int tag; // the block tag 
		float distance; // The raw distance to the collision point
		float perpindcularDistance; // The perpindicular distance [1/(Ray Direction in X or Y)]
		float u; // The u coordinate of the collision
	};


}