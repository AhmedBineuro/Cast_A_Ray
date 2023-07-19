#include "Map_Reader.h"
void printSegment(Segment segment) {
	std::cout << "Segment: " << segment.name << std::endl;
	for (const std::string line : segment.contents) {
		std::cout << line << std::endl;
	}
}
Map_Reader::Map_Reader() {
	m_segments = std::vector<Segment>(0);
}
void Map_Reader::processLevel(std::string URL) {
	// Reject any files that don't contain the .car or .CAR level file. This will crash the app
	if (URL.size() < 4 || !((URL.substr(URL.size() - 4) == ".car") || (URL.substr(URL.size() - 4) == ".CAR")))
	{
			std::cerr << "Invalid file type. Expected .car file." << std::endl;
			return;
	}
	std::ifstream file(URL);
	if (!file) {
		std::cerr << "Failed to open File" << std::endl;
		return;
	}
	std::string currentLine;
	Segment currentSegment;
	//Read the file line by line
	while (std::getline(file,currentLine)) {
		// Ignore the comments and empty lines
		if (currentLine.empty()||currentLine[0]=='/')
			continue;
		//If a new segment started
		if (currentLine[0] == '#' && currentLine[currentLine.length() - 1] == ':')
		{
			//Save previous segment if we had one
			if (!currentSegment.name.empty())
				m_segments.push_back(currentSegment);
			int start = (currentLine[1] == ' ') * 1 + 1;
			int end = (currentLine[currentLine.length() - 2] == ' ') * 2 + 2;
			currentSegment.name = currentLine.substr(start, currentLine.length() - end);
			currentSegment.contents.clear();
		}
		else if (currentLine == "#") {
			m_segments.push_back(currentSegment);
			currentSegment.name.clear();
			currentSegment.contents.clear();
		}
		else {
			currentSegment.contents.push_back(currentLine);
		}
	}
}
std::vector<Segment> Map_Reader::getAllSegments() { return m_segments; }
Segment Map_Reader::getSegment(std::string SegmentName) {
	for (const Segment segment : m_segments) {
		if (segment.name == SegmentName)
			return segment;
	}
	return Segment();
}
std::vector<int> Map_Reader::stringToVector(std::string vect) {
	std::vector<int> output(0);
	std::string currentNumber="";
	for (char c : vect) {
		if (((int(c) >= 48) && (int(c) <= 57)) ||((c == '-') && (currentNumber=="")))
		{
			currentNumber += c;
		}
		else if (currentNumber != "") {
			int value = std::stoi(currentNumber);
			output.push_back(value);
			currentNumber = "";
		}

	}
	if (currentNumber != "") {
		int value = std::stoi(currentNumber);
		output.push_back(value);
		currentNumber = "";
	}
	return output;
}
void Map_Reader::printVector(std::vector<int>vect) {
	for (int i = 0; i < vect.size();i++) {
		std::cout << vect[i];
		if (i != vect.size() - 1) {
			std::cout << ",";
		}
	}
}

/**
* @todo Implement block to texture mapping and resource list loading
* @todo Create a data structure to help to create a two way link between textures and the block tags
*/
MapInfo Map_Reader::processLayoutInfo() {
	MapInfo output;
	std::cout << "PROCESSING START\n";
	Segment currentSegment=this->getSegment("floor layout");
	output.maxWidth = 0;
	for (std::string row : currentSegment.contents)
	{
		output.floor_layout.push_back(stringToVector(row));
		int width = output.floor_layout.back().size();
		output.maxWidth = (output.maxWidth >= width) * output.maxWidth + (output.maxWidth < width) * width;
	}
	output.maxHeight = output.floor_layout.size();

	currentSegment = this->getSegment("wall layout");
	for (std::string row : currentSegment.contents)
	{
		output.wall_layout.push_back(stringToVector(row));
	}
	currentSegment = this->getSegment("ceiling layout");
	for (std::string row : currentSegment.contents)
	{
		output.ceiling_layout.push_back(stringToVector(row));
	}
	std::cout << "Done\n";
	return output;
}