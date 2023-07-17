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
	if (URL.size() < 4 || !((URL.substr(URL.size() - 4) == ".car") || (URL.substr(URL.size() - 4) == ".CAR")))
	{
			std::cerr << "Invalid file type. Expected .car file." << std::endl;
			throw std::invalid_argument("Invalid file type. Expected .car file.");
	}
	std::ifstream file(URL);
	if (!file) {
		std::cerr << "Failed to open File" << std::endl;
		return;
	}
	std::string currentLine;
	Segment currentSegment;
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
			int end = (currentLine[currentLine.length() - 2] == ' ') * 1 + 2;
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