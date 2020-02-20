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

    void run(std::vector<Library *> &libraries);

    uInt metric;
    ctpl::thread_pool m_threadpool;
};

#endif
