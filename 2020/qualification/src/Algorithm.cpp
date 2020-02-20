#include "../lib/Algorithm.h"
#include <iostream>

void Algorithm::run(std::vector<Library *> &libraries)
{
    for (int i = 0; i != libraries.size(); ++i) {
        Library &lib = *libraries[i];
        metric = lib.N * lib.M / lib.T;
    }
}

void Algorithm::run2(uInt D, std::vector<Library *> &libraries, uIntVector& bookScores, uIntVector& librariesToSignUp) {
	uInt day = 0;

	std::vector<Library *> librariesTmp = libraries;

	std::vector<bool> bookUsed;
	bookUsed.reserve(bookScores.size());

	for (uInt i = 0; i < bookScores.size(); ++i) {
		bookUsed.push_back(false);
	}

	uInt signupTime = 0;

	uIntVector lastUsedBookIndex;
	lastUsedBookIndex.reserve(libraries.size());

	for (uInt i = 0; i < libraries.size(); ++i) {
		lastUsedBookIndex.push_back(0);
	}


	Library* nextLib = NULL;
	// Only add book once signed up!
	while (day < D) {
		if (signupTime == 0) {
			if (nextLib != NULL) {
				librariesToSignUp.push_back(nextLib->id);
			}
		}
		for (uInt i = 0; i < librariesToSignUp.size(); ++i) {
			Library* lib = libraries[librariesToSignUp[i]];
			uInt id = lib->id;
			uInt booksPerDay = lib->T;
			for (int j = 0; j < booksPerDay; ++j) {
				uInt nextBookIndex = lastUsedBookIndex[id];
				if (nextBookIndex > lib->bookIds.size()) { // Library finished
					continue;
				}
				uInt bookId = lib->bookIds[nextBookIndex];

				++lastUsedBookIndex[id];

				if (bookUsed[bookId] == true) {
					--j;
					continue;
				}

				lib->bookIdsToScan.push_back(bookId);

				bookUsed[bookId] = true;
			}
		}

		if (signupTime != 0) {
			--signupTime;
			++day;
			continue;
		}


		// Select new library to add;
		nextLib = getNextLibrary(librariesTmp);
		if (nextLib == NULL) { // FINISHED
			break;
		}

		std::vector<Library *>::iterator it = std::find(librariesTmp.begin(), librariesTmp.end(), nextLib);
		if (it == librariesTmp.end()) {
			std::cout << "SOMETHING WENT WRONG!" << std::endl;
			return;
		}
		librariesTmp.erase(it);

		signupTime = nextLib->M - 1;


		++day;
	}
}

Library* Algorithm::getNextLibrary(std::vector<Library *>& librariesTmp) {
	Library* libReturn = NULL;

	uInt bestSignUp = 0xFFFFFFF;
	uInt ratePerDay = 0;

	for (uInt i = 0; i < librariesTmp.size(); ++i) {
		Library* lib = librariesTmp[i];
		if (lib->M <= bestSignUp && lib->T >= ratePerDay) {
			libReturn = lib;
			bestSignUp = lib->M;
			ratePerDay = lib->T;
		}
	}

	return libReturn;
}
