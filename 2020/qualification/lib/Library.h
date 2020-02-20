#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>
#include <string>
#include "Defines.h"

class Library {
public:
	Library(uInt _id, uInt _numBooks, uInt _time, uInt _shippable, uInt _nbBooksToScan);
    virtual ~Library() {}

    uInt id;

    uInt numberOfBooks;
    uInt signupTime;
    uInt booksShippablePerDay;

    uIntVector bookIds;

    uInt numberOfBooksToScan;
    uIntVector bookIdsToScan;
};

#endif
