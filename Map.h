
#pragma once
#include "Core.h"
#include "Map_Reader.h"
#include "Log.h"
class Map {
public:
	Map();
	void load_level(MapInfo map_details);
	void draw(sf::RenderTarget& renderTarget);
	void draw(sf::RenderTarget& renderTarget,sf::RenderStates);
	
	void drawMinimap(sf::RenderTarget& renderTarget);
	void drawMinimap(sf::RenderTarget& renderTarget, sf::RenderStates);
	void setMiniPosition();

	// Function to translate the floating point position to a tile index position
	sf::Vector2i toTileCoord(sf::Vector2f position);
	// Function to translate the tile index position to a floating point position
	sf::Vector2f toLiteralCoord(sf::Vector2i position);
	//Function to check if the position is still in map bounds or not
	//@note check with tile Index position
	bool isInBounds(sf::Vector2f position);

	//Functions to interact with the log
	bool linkLog();
	void unlinkLog();


private:
	sf::Vector2f m_minimapPosition;
	sf::Vector2f m_minimapDimensions;
	sf::RectangleShape m_minimapBackground, m_tileSprite;
	Log* m_linkedLog;
};