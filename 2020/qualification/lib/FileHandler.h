#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <vector>
#include <string>
#include "Defines.h"
#include "Library.h"

class FileHandler {
public:
	FileHandler() {}
    virtual ~FileHandler() {}

    bool parseInputFile(std::string fileName, uInt& B, uInt& L, uInt& D, uIntVector& bookScores, std::vector<Library*>& libraries);

    bool writeOutputFile(std::string fileName);
};

#endif
