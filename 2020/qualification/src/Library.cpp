#include "../lib/Library.h"
#include <iostream>


Library::Library(uInt _id, uInt _numBooks, uInt _time, uInt _shippable)
    : id(_id)
    , N(_numBooks)
    , M(_time)
    , T(_shippable)
    , book_score(0)
    , already_shipping(false)
{
    bookIds.reserve(N);
}
