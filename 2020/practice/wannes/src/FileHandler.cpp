
#include "../lib/FileHandler.h"
#include <iostream>
#include <sstream>
#include <fstream>

bool FileHandler::parseInputFile(std::string fileName, unsigned int& numberOfSlices, std::vector<unsigned int>& slicesCount) {
	std::ifstream input(fileName);

	// Read first line
	std::string line;
	std::getline(input, line);

	unsigned int numberOfPizzas;
	std::istringstream iss(line);
	if (!(iss >> numberOfSlices >> numberOfPizzas)) {
		return false;
	}

	slicesCount.reserve(numberOfPizzas);

	// Read second line
	std::getline(input, line);
	iss.clear();
	iss.str(line);

	for (unsigned int i = 0; i < numberOfPizzas; ++i) {
		unsigned int val = 0;
		iss >> val;
		slicesCount.push_back(val);
	}
	return true;
}

bool FileHandler::writeOutputFile(std::string fileName, std::vector<unsigned int>& pizzasToOrder) {
	std::ofstream outFile;
	outFile.open (fileName);
	outFile << pizzasToOrder.size() << "\n";
	for (unsigned int i = 0; i < pizzasToOrder.size(); ++i) {
		outFile << pizzasToOrder[i] << " ";
	}
	outFile.close();
	return true;
}
