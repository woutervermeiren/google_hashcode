#include "../lib/Algorithm.h"
#include <iostream>
#include <numeric>
#include <thread>
#include <chrono>
#include <algorithm>
using namespace std::chrono_literals;

void Algorithm::run(uInt D, std::vector<Library *> &libraries, uIntVector& bookScores, uIntVector& librariesToSignUp) {
	uInt day = 0;

	std::vector<Library *> librariesTmp = libraries;

	std::vector<bool> bookUsed;
	std::vector<bool> bookWillBeUsed;
	bookUsed.reserve(bookScores.size());
	bookWillBeUsed.reserve(bookScores.size());

	for (uInt i = 0; i < bookScores.size(); ++i) {
		bookUsed.push_back(false);
		bookWillBeUsed.push_back(false);
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
		//std::cout << "day " << day << "/" << D << std::endl;
		if (signupTime == 0) {
			if (nextLib != NULL) {
				librariesToSignUp.push_back(nextLib->id);
				addBooksThatWillBeUsed(bookWillBeUsed, D-day, nextLib);
			}
		}
		for (uInt i = 0; i < librariesToSignUp.size(); ++i) {
			Library* lib = libraries[librariesToSignUp[i]];
			uInt id = lib->id;

			if (lastUsedBookIndex[id] >= lib->bookIds.size()) { // Library finished
				continue;
			}

			uInt booksPerDay = lib->T;
			for (int j = 0; j < booksPerDay; ++j) {
				uInt nextBookIndex = lastUsedBookIndex[id];
				if (nextBookIndex >= lib->bookIds.size()) { // Library finished
					continue;
				}
				uInt bookId = lib->bookIds[nextBookIndex].first;

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

		nextLib = getNextLibrary(librariesTmp, D-day, bookWillBeUsed);

		if (nextLib == NULL) { // FINISHED
			++day;
			continue;
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

Library* Algorithm::getNextLibrary(std::vector<Library *>& librariesTmp, uInt daysLeft, std::vector<bool>& bookUsed) {
	Library* libReturn = NULL;

	uInt bestScore = 0;

	for (uInt i = 0; i < librariesTmp.size(); ++i) {
		Library* lib = librariesTmp[i];
		uInt signUpTime = lib->M;

		int booksToAdd = daysLeft - signUpTime;

		booksToAdd *= lib->T;

		if (booksToAdd <= 0) {
			continue;
		}
		uInt score = 0;

		uInt index = 0;
		for (int j = 0; j < booksToAdd; ++j) {
			if (index >= lib->bookIds.size()) {
				break;
			}
			uInt bookId = lib->bookIds[index].first;
			if (bookUsed[bookId] == true) {
				--j;
				++index;
				continue;
			}
			score += lib->bookIds[index].second;

			++index;
		}

		score /= lib->M;
		if (score > bestScore) {
			bestScore = score;
			libReturn = lib;
		}
	}


	return libReturn;
}

void Algorithm::addBooksThatWillBeUsed(std::vector<bool>& bookWillBeUsed, uInt daysLeft, Library* lib) {
	uInt index = 0;
	for (uInt i = 0; i < daysLeft * lib->T; ++i) {
		if (index >= lib->bookIds.size()) {
			break;
		}

		uInt bookId = lib->bookIds[index].first;
		if (bookWillBeUsed[bookId] == true) {
			--i;
			++index;
			continue;
		}
		bookWillBeUsed[bookId] = true;

		++index;
	}
}
