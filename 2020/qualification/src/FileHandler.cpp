
#include "../lib/FileHandler.h"
#include <iostream>
#include <sstream>
#include <fstream>

bool FileHandler::parseInputFile(std::string fileName, uInt& B, uInt& L, uInt& D, uIntVector& bookScores, std::vector<Library*>& libraries) {
	std::ifstream input(fileName);

	// Read first line
	std::string line;
	std::getline(input, line);

    std::istringstream iss(line);
    if (!(iss >> B >> L >> D)) {
            return false;
    }

    // Read second line
    std::getline(input, line);
    iss.clear();
    iss.str(line);

    for (uInt i = 0; i < B; ++i) {
    	uInt val = 0;
    	iss >> val;
    	bookScores.push_back(val);
    }

    for (uInt i = 0; i < L; ++i) {
        std::getline(input, line);
        iss.clear();
        iss.str(line);

        uInt nbBooks;
        uInt signupTime;
        uInt shippablePerDay;

        iss >> nbBooks >> signupTime >> shippablePerDay;

        std::getline(input, line);
		iss.clear();
		iss.str(line);

		Library* library = new Library(i, nbBooks, signupTime, shippablePerDay);

		libraries.push_back(library);
		for (uInt j = 0; j < nbBooks; ++j) {
		   	uInt val = 0;
			iss >> val;
			library->bookIds.push_back(val);
		}
    }

	return true;
}

bool FileHandler::writeOutputFile(std::string fileName) {
	std::ofstream outFile;
	outFile.open (fileName);

	return true;
}
