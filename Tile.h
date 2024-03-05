#pragma once
#include "Core.h"
class Tile {
public:
	Tile(); //Set the value to 0 with the block_ray property to false
	Tile(TileId ids);
	//These are the drawing function for minimap
	void drawMini(sf::RenderTarget&renderTarget);
	void drawMini(sf::RenderTarget& renderTarget,sf::RenderStates & states);
	TileID getTileID(); //Gets the ID's associated with the tile
	int getFloorID();
	int getWallID();
	int getCeilingID();
	//Function to set the dimensions of the minimap representation
	void setMiniColor(sf::Color newColor);
	void setSize(float size);
	void setPosition(sf::Vector2f position);
private:

	TileID m_tileID;
	float m_size; //Will be used to calculate the offset between vertices
	/**
	* @ brief special properties is a bit feild for all the special property flags
	* We have 8 bits:
	* xxxx xxx1 : is solid
	* xxxx xx1x : is transparent
	* xxxx x1xx : is portal
	* xxxx 1xxx : is interactable
	* xxx1 xxxx : toggle state
	* Last 3 bits will be set to 0 by default
	*/
	char m_special_properties;
	sf::Color m_miniColor;
	sf::VertexArray sprite;
};