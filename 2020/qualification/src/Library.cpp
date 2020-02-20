#include "../lib/Library.h"
#include <iostream>

Library::Library(uInt _id, uInt _numBooks, uInt _time, uInt _shippable,  uInt _nbBooksToScan) : id(_id), numberOfBooks(_numBooks),
	signupTime(_time), booksShippablePerDay(_shippable), numberOfBooksToScan(_nbBooksToScan) {
	bookIds.reserve(numberOfBooks);
}
