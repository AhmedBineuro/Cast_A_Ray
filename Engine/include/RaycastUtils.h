#pragma once
#include "Core\include\Map.h"
#include <limits>
#include <SFMLMath.hpp>
namespace RaycastUtils {
	struct RayCollisionInfo {
		bool noHit=false;// True if the ray didn't collide with anything
        bool outOfBounds = false;
		int side; // 0 for East/West or 1 for North/South
		int tag; // the block tag 
		//double distance; // The raw distance to the collision point
		double distance; // The distance to the collision point
		float u; // The u coordinate of the collision
        sf::Vector2i wallPosition;
	};
	inline RayCollisionInfo castRay(sf::Vector2f position, sf::Vector2f direction, const Map& m,float renderDistance=200.0f){
    RaycastUtils::RayCollisionInfo output;
	sf::Vector2f ray = direction;
    //Reversed because the array is divided into rows of elements in a 2D matrix 
    sf::Vector2i originalPosition(floor(position.x), floor(position.y));
    sf::Vector2i tileIndex(floor(position.y), floor(position.x)); // Will be manipulated

    /*double axisWeightX = sqrt(1 + (direction.y * direction.y) / (direction.x * direction.x));
    double axisWeightY = sqrt(1 + (direction.x * direction.x) / (direction.y * direction.y));
    */
    double axisWeightX, axisWeightY;
    if (direction.x != 0)
    {
        // Given a value of x what is the value of y
        axisWeightX = abs(1 / direction.x);
    }
    else
    {
        axisWeightX = 1e30;
    }
    if (direction.y != 0)
    {
        // Given a value of y what is the value of x
        axisWeightY = abs(1 / direction.y);
    }
    else
    {
        axisWeightY = 1e30;
    }

    //Get the X and Y axis distances and step directions
    double xDist = 0, yDist = 0;
    int xStepDirection = 0;
    int yStepDirection = 0;
    if (direction.x > 0)
    {
        xDist =originalPosition.x + 1 - position.x;
        xStepDirection = 1;
    }
    else
    {
        xDist = position.x - originalPosition.x;
        xStepDirection = -1;
    }
    if (direction.y > 0)
    {
        yDist = originalPosition.y + 1 - position.y;
        yStepDirection = 1;
    }
    else
    {
        yDist = position.y - originalPosition.y;
        yStepDirection = -1;
    }
    xDist *= axisWeightX;
    yDist *= axisWeightY;
    
    //DDA Iterative step
    bool hit = false;
    while (!hit) {
        if (xDist < yDist)
        {
            xDist += axisWeightX;
            tileIndex.y += xStepDirection;
            output.side = 0;
        }
        else {
            yDist += axisWeightY;
            tileIndex.x += yStepDirection;
            output.side = 1;
        }
        if (tileIndex.x >= 0 && tileIndex.x < m.walls.size() && (tileIndex.y >= 0 && tileIndex.y < m.walls[tileIndex.x].size())) {
            if (std::find(m.ignoreRaycast.begin(), m.ignoreRaycast.end(),m.walls[tileIndex.x][tileIndex.y]) == m.ignoreRaycast.end()) {
                output.tag = m.walls[tileIndex.x][tileIndex.y];
                hit = true;
                break;
            }
        }
        if (renderDistance<=xDist&& renderDistance <= yDist) {
            output.noHit = true;
            break;
        }
    }
    output.wallPosition = tileIndex;
    //Get distances and wall coordinates
    if (output.side && hit) {
        output.distance = yDist-axisWeightY ;
        output.u = (output.distance * ray.x+ position.x)-originalPosition.x;
    }
    else if(hit){
        output.distance = xDist - axisWeightX;
        output.u = (output.distance * ray.y + position.y)- originalPosition.y;
    }
    else output.distance = sf::getLength(sf::getClamped(sf::Vector2f(xDist, yDist), 0.0f, renderDistance));
    output.u-=floor(output.u);
    output.u += 1 * (output.u < 0);

    return output;
}
}