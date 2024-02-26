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
	inline RayCollisionInfo castRay(sf::Vector2f position, sf::Vector2f direction, Map m,float renderDistance=200.0f){
    RaycastUtils::RayCollisionInfo output;
    if (position.y > m.walls.size())
    {
        output.noHit = true;
        return output;
    }
    else if (position.x > m.walls[(int)position.y].size())
    {
        output.noHit = true;
        return output;
    }
	sf::Vector2f ray = direction;
    //Reversed because the array is divided into rows of elements in a 2D matrix 
    sf::Vector2i originalPosition((int)position.x, (int)position.y);
    sf::Vector2i tileIndex((int)position.y, (int)position.x); // Will be manipulated

    double axisWeightX = 0;
    double axisWeightY = 0;
    if (direction.x != 0)
    {
        // Given a value of x what is the value of y
        axisWeightX = abs(1.0f / direction.x);
    }
    else
    {
        axisWeightX = 1e30;
    }
    if (direction.y != 0)
    {
        // Given a value of y what is the value of x
        axisWeightY = abs(1.0f / direction.y);
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
        xDist = abs(originalPosition.x + 1 - position.x);
        xStepDirection = 1;
    }
    else
    {
        xDist = abs(position.x - originalPosition.x);
        xStepDirection = -1;
    }
    if (direction.y > 0)
    {
        yDist = abs(originalPosition.y + 1 - position.y);
        yStepDirection = 1;
    }
    else
    {
        yDist = abs(position.y - originalPosition.y);
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
        if (xDist > renderDistance&& yDist > renderDistance&&!hit) {
            output.noHit = true;
            break;
        }
        bool xIndex = tileIndex.x >= 0 || tileIndex.x < m.walls.size();
        bool yIndex = false;
        if (xIndex)
        {
            yIndex = (tileIndex.y >= 0 || tileIndex.y < m.walls[tileIndex.x].size());
        }
        if (xIndex && yIndex) {
            //if (std::find(m.ignoreRaycast.begin(), m.ignoreRaycast.end(),m.walls[tileIndex.x][tileIndex.y]) == m.ignoreRaycast.end()) {
            if (m.walls[tileIndex.x][tileIndex.y]!=0) {
                output.tag = m.walls[tileIndex.x][tileIndex.y];
                hit = true;
            }
        }
        else {
            output.noHit = true;
            hit = true;
        }
    }
    //Get distances and wall coordinates
    if (output.side) {
        output.distance = yDist;
        output.perpindcularDistance = yDist - axisWeightY;
        output.u = (output.perpindcularDistance * ray.x+ position.x)-tileIndex.y;
    }
    else {
        output.distance = xDist;
        output.perpindcularDistance = xDist - axisWeightX;
        output.u = (output.perpindcularDistance * ray.y + position.y)-tileIndex.x;
    }
    output.u-=floor(output.u);
    output.u += 1 * (output.u < 0);
    //std::cout << "Perpindicular Distance " << output.u << std::endl;
    return output;
}

}