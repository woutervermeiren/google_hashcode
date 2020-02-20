#include "../lib/Library.h"
#include <iostream>

Library::Library(uInt _id, uInt _numBooks, uInt _time, uInt _shippable)
    : id(_id)
    , N(_numBooks)
    , T(_time)
    , M(_shippable)
{
    bookIds.reserve(N);
}
