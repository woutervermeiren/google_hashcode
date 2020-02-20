#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>
#include <string>
#include "Defines.h"

class Library {
public:
	Library(uInt _id, uInt _numBooks, uInt _time, uInt _shippable);
    virtual ~Library() {}

    uInt id;

    uInt numberOfBooks;
    uInt signupTime;
    uInt booksShippablePerDay;

    uIntVector bookIds;
};

#endif
