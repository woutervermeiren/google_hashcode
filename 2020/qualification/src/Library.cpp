#include "../lib/Library.h"
#include <iostream>


Library::Library(uInt _id, uInt _numBooks, uInt _time, uInt _shippable)
    : id(_id)
    , N(_numBooks)
    , M(_time)
    , T(_shippable)
    , done(false)
{
    bookIds.reserve(N);
}
