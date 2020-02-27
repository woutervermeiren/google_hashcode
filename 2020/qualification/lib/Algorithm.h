#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "Defines.h"
#include "Library.h"
#include <string>
#include <vector>
#include "threadpool.h"

class Algorithm
{
public:
    Algorithm() {}
    virtual ~Algorithm() {}

    void run(uInt D, std::vector<Library *> &libraries, uIntVector& bookScores, uIntVector& librariesToSignUp);

    Library* getNextLibrary(std::vector<Library *>& librariesTmp, uInt daysLeft, std::vector<bool>& bookUsed);

    void addBooksThatWillBeUsed(std::vector<bool>& bookWillBeUsed, uInt daysLeft, Library* nextLib);
};

#endif
