#include "../lib/Library.h"
#include <iostream>

Library::Library(uInt _id, uInt _numBooks, uInt _time, uInt _shippable, uInt _nbBooksToScan)
    : id(_id)
    , N(_numBooks)
    , M(_time)
    , T(_shippable)
    , numberOfBooksToScan(_nbBooksToScan)
{
    bookIds.reserve(N);
}
