#include "../lib/Library.h"
#include <iostream>


Library::Library(uInt _id, uInt _numBooks, uInt _time, uInt _shippable)
    : id(_id)
    , N(_numBooks)
    , M(_time)
    , T(_shippable)
    , already_shipping(false)
{
    bookIds.reserve(N);
}
