#pragma once
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <vector>
/**
* @brief A struct containing the name and contents of a segment
* The struct keeps a string for the name and a vector of strings for each line of the segment's contents 
*/
static struct Segment {
	std::string name;
	std::vector<std::string> contents;
};
/**
* @brief Function to print a given segment in a formatted form
* @param segment 
*/
void printSegment(Segment segment);
/**
* @brief Class to read a level file, parses, and processes it to Segment type objects
* The class contains a vector of Segment type objects that gets filled up with all the segments found in the file.
* The class does not check for necessary segments like the level layout 
*/
class Map_Reader {
public:
	Map_Reader();
	/**
	* @brief Function to process a.car file and extracts the segments inside onto a vector
	* Function to process a.car file and extracts the segments inside
	* onto a vector.The vector contains all the information segments
	* contained in the file inside a Segment object.
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
private:
	std::vector<Segment> m_segments;
};
	
	
