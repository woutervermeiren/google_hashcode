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

    void run(std::vector<Library *> &libraries, uIntVector &book_scores);

    uInt metric;
    ctpl::thread_pool m_threadpool;
};

#endif
