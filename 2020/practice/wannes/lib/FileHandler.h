#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <vector>
#include <string>

class FileHandler {
public:
	FileHandler() {}
    virtual ~FileHandler() {}

    bool parseInputFile(std::string fileName, unsigned int& numberOfSlices, std::vector<unsigned int>& slicesCount);

    bool writeOutputFile(std::string fileName, std::vector<unsigned int>& pizzasToOrder);
};

#endif
