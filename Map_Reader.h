#pragma once
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <map>
#include "Map.h"
#include "Core.h"
/**
* @struct
* @brief A struct containing the name and contents of a segment.
* The struct keeps a string for the name and a vector of strings for each line of the segment's contents 
*/
struct Segment {
	std::string name;
	std::vector<std::string> contents;
};


/**
* @struct
* @brief A struct containing processed map data.
* The struct will contain all the information that can be processed. The resource list will contain
* all the URLs for all the resources needed to be loaded (sounds, images, videos, etc).
* The maxWidth attribute is there to help estimate the maximum footprint of drawing the map as a minimap.
*/
struct MapInfo {
	std::vector< std::vector<int>> floor_layout;
	std::vector< std::vector<int>> wall_layout;
	std::vector< std::vector<int>> ceiling_layout;
	std::vector<ResourceInfo> resourceList;
	int maxWidth;
	int maxHeight;
};


/**
* @brief Function to print a given segment in a formatted form.
* @param segment 
*/
void printSegment(Segment segment);
/**
* @brief Class to read a level file, parses, and processes it to Segment type objects.
* The class contains a vector of Segment type objects that gets filled up with all the segments found in the file.
* The class does not check for necessary segments like the level layout 
*/
class Map_Reader {
public:
	Map_Reader();
	/**
	* @brief Function to process a.car file and extracts the segments inside onto a vector.
	* Function to process a.car file and extracts the segments inside onto a vector.The vector contains all the information segments contained in the file inside a Segment object.
	* @param URL Is the url to the level file
	* @throws invalid argument exception
	*/
	void processLevel(std::string URL);

	/**
	* @brief Function to get a copy of one of the segments.
	* @param SegmentName The name of the segment (EXCLUDING # AND :)
	* @return A Segment object containing the information. Will return an empty Segment object if there is no such segment
	*/
	Segment getSegment(std::string SegmentName);
	/**
	* @brief Function to get a copy all of the segments.
	* @return A vector of Segment objects.
	*/
	std::vector<Segment> getAllSegments();

	/**
	* @brief Function to process the segment information into a Map object.
	* This function will start the processing of the text information in the segment to the actual map.The function then return true if there is no errors during the map processing.A return value of false means that there is some missing necessarry information required to build the map (such as wall and floor layouts).
	* @param map A CAR map
	* @return success status.
	*/
	/**
	* @brief Function to process a string of comma seperated numbers to a vector.
	* @param vect A string of comma seperated integers.
	* @return a vector of ints.
	*/
	static std::vector<int> stringToVector(std::string vect);

	/**
	* @brief Function to print an integer vector into the console.
	* @param vect Vector 
	*/
	static void printVector(std::vector<int> vect);
	/**
	* @brief Function to split a string using a specific token
	* 
	* @param str The input string
	* @param token The character to split around
	* @return a vector containing the divided strings
	*/
	static std::vector<std::string> splitString(std::string str,char token);

	bool linkMap(Map &map);
	/**
	* @brief Function to create a Map object from the segment information .
	* This function will start the processing of the text information in the segment
	* a map. The function then return the map if everything was successfull and will return null if there is some missing necessarry information 
	* required to build the map (such as wall and floor layouts).
	* @return processed map object.
	*/
	Map createMap();

	/**
	* @brief Function to process layout related segments and return it as a map .
	* This function will start the processing of the text information in the segment
	* a map. The function then return the map if everything was successfull and will return null if there is some missing necessarry information
	* required to build the map (such as wall and floor layouts).
	* @return processed map object.
	*/
	MapInfo processLayoutInfo();



private:
	std::vector<Segment> m_segments;
};
	
	
