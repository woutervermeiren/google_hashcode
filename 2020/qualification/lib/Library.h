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

    uInt N;
    uInt T;
    uInt M;

    uIntVector bookIds;
};

#endif
