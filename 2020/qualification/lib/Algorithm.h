#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "Defines.h"
#include "Library.h"
#include <string>
#include <vector>

class Algorithm
{
public:
    Algorithm() {}
    virtual ~Algorithm() {}

    void run(std::vector<Library *> &libraries);

    void run2(uInt D, std::vector<Library *> &libraries, uIntVector& bookScores, uIntVector& librariesToSignUp);

    Library* getNextLibrary(std::vector<Library *>& librariesTmp);

    uInt metric;
};

#endif
