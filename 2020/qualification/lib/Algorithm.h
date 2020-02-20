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

    uInt metric
};

#endif
