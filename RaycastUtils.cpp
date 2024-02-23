#include "RaycastUtils.h"
RaycastUtils::RayCollisionInfo RaycastUtils::castRay(sf::Vector2f position, sf::Vector2f direction, Map m, float renderDistance) {
    RaycastUtils::RayCollisionInfo output;
    if (position.y >= m.walls.size())
    {
        output.noHit = true;
        return output;
    }
    else if (position.x >= m.walls[(int)position.x].size())
    {
        output.noHit = true;
        return output;
    }
	sf::Vector2f ray = direction;
    //Reversed because the array is divided into rows of elements in a 2D matrix 
    sf::Vector2i originalPosition((int)position.y, (int)position.x);
    sf::Vector2i tileIndex((int)position.y, (int)position.x); // Will be manipulated

	sf::Vector2f axisWeights(0,0);
    if (direction.x != 0)
    {
        // Given a value of x what is the value of y
        axisWeights.x = abs(1.0f / direction.x);
    }
    else
    {
        axisWeights.x = 1e30;
    }
    if (direction.y != 0)
    {
        // Given a value of y what is the value of x
        axisWeights.y = abs(1.0f / direction.y);
    }
    else
    {
        axisWeights.y = 1e30;
    }
    //Get the X and Y axis distances and step directions
    float xDist = 0, yDist = 0;
    int xStepDirection = 0;
    int yStepDirection = 0;
    if (direction.x > 0)
    {
        xDist = abs(tileIndex.y + - position.x);
        xStepDirection = 1;
    }
    else
    {
        xDist = abs(position.x - tileIndex.y);
        xStepDirection = -1;
    }
    if (direction.y > 0)
    {
        yDist = abs(tileIndex.x - position.y);
        yStepDirection = 1;
    }
    else
    {
        yDist = abs(position.y - tileIndex.x);
        yStepDirection = -1;
    }
    xDist *= axisWeights.x;
    yDist *= axisWeights.y;
    
    //DDA Iterative step
    bool hit = false;
    while (!hit) {
        if (xDist < yDist)
        {
            xDist += axisWeights.x;
            tileIndex.y += xStepDirection;
            output.side = 0;
            if (xDist >= renderDistance) {
                output.noHit = true;
                break;
            }
        }
        else {
            yDist += axisWeights.y;
            tileIndex.x += yStepDirection;
            output.side = 1;
            if (yDist >= renderDistance) {
                output.noHit = true;
                break;
            }
        }
        if (std::find(m.ignoreRaycast.begin(), m.ignoreRaycast.end(), m.walls[tileIndex.x][tileIndex.y]) == m.ignoreRaycast.end()) {
            output.tag = m.walls[tileIndex.x][tileIndex.y];
            hit = true;
        }
    }
    //Get distances and wall coordinates
    if (output.side) {
        output.distance = yDist;
        output.perpindcularDistance = yDist - axisWeights.y;
        output.u = position.y + (output.perpindcularDistance * ray.y);
    }
    else {
        output.distance = xDist;
        output.perpindcularDistance = xDist - axisWeights.x;
        output.u = position.x + (output.perpindcularDistance * ray.x);
    }
    output.u -= floor(output.u);

    return output;
}