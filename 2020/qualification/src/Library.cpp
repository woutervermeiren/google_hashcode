#include "../lib/Library.h"
#include <iostream>

Library::Library(uInt _id, uInt _numBooks, uInt _time, uInt _shippable) : id(_id), numberOfBooks(_numBooks),
	signupTime(_time), booksShippablePerDay(_shippable) {
	bookIds.reserve(numberOfBooks);
}
