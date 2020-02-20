#ifndef LIBRARY_H
#define LIBRARY_H

#include "Defines.h"
#include <string>
#include <vector>

class Library
{
public:
    Library(uInt _id, uInt _numBooks, uInt _time, uInt _shippable, uInt _nbBooksToScan);
    virtual ~Library() {}

    uInt id;

    uInt N;
    uInt T;
    uInt M;

    uIntVector bookIds;

    uInt numberOfBooksToScan;
    uIntVector bookIdsToScan;
};

#endif
