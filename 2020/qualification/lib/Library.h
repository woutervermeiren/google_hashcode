#ifndef LIBRARY_H
#define LIBRARY_H

#include "Defines.h"
#include <string>
#include <vector>

class Library
{
public:
	Library(uInt _id, uInt _numBooks, uInt _time, uInt _shippable);

    uInt get_book_score() { return 5; }

    virtual ~Library() {}

    void sort();

    uInt id;

    // Book count
    uInt N;
    // Startup time
    uInt T;
    // Book processing rate per day
    uInt M;

    uInt book_score;

    uIntPairVector bookIds;

    uIntVector bookIdsToScan;

    bool already_shipping;
};

#endif
