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
    Algorithm() : metric(0), today(0), days_till_signup_done(0), library_count(0) {}
    virtual ~Algorithm() {}

    void run(std::vector<Library *> &libraries, uIntVector &book_scores, uInt D);

    uInt metric;
    ctpl::thread_pool m_threadpool;

    void run(std::vector<Library *> &libraries);
    Library* get_next_library(std::vector<Library *> &libraries);

    uInt today;
    uInt days_till_signup_done;
    uInt library_count;
};

#endif
