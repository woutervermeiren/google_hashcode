#ifndef LIBRARY_H
#define LIBRARY_H

#include "Defines.h"
#include <string>
#include <vector>

class Library
{
public:
	Library(uInt _id, uInt _numBooks, uInt _time, uInt _shippable);

    virtual ~Library() {}

    uInt id;

    // Book count
    uInt N;
    // Startup time
    uInt T;
    // Book processing rate per day
    uInt M;

    uIntVector bookIds;

    uIntVector bookIdsToScan;
};

#endif
