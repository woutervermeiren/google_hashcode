#include "../lib/Library.h"
#include <iostream>
#include <algorithm>


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

bool sortbysec(const std::pair<unsigned int,unsigned int> &a,  const std::pair<unsigned int,unsigned int> &b)
{
    return (a.second > b.second);
}

void Library::sort() {
	std::sort(bookIds.begin(), bookIds.end(), sortbysec);
}
