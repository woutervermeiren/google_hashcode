#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <vector>
#include <string>

class FileHandler {
public:
	FileHandler() {}
    virtual ~FileHandler() {}

    bool parseInputFile(std::string fileName);

    bool writeOutputFile(std::string fileName);
};

#endif
