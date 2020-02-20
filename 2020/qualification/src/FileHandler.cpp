
#include "../lib/FileHandler.h"
#include <iostream>
#include <sstream>
#include <fstream>

bool FileHandler::parseInputFile(std::string fileName) {
	std::ifstream input(fileName);

	// Read first line
	std::string line;
	std::getline(input, line);

	return true;
}

bool FileHandler::writeOutputFile(std::string fileName) {
	std::ofstream outFile;
	outFile.open (fileName);

	return true;
}
