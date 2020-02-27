#include "../lib/Algorithm.h"
#include <iostream>
#include <numeric>
#include <thread>
#include <chrono>
#include <algorithm>
using namespace std::chrono_literals;

void Algorithm::run(std::vector<Library *> &libraries, uIntVector &book_scores, uInt D, uIntVector& librariesToSignUp)
{
    library_count = libraries.size();

    // now step through days
    while(today < D && library_count != 0) {
        // select next library that can start sending books
        Library* lib = nullptr;
        if(days_till_signup_done == 0) {
            calculate_book_scores(libraries, book_scores);

            lib = get_next_library(libraries, D - today);
            days_till_signup_done = lib->M;

            librariesToSignUp.push_back(lib->id);
        }

        days_till_signup_done--;
        today++;
    }


}

Library* Algorithm::get_next_library(std::vector<Library *> &libraries, uInt days_left_till_project_done) {
    Library* lib = nullptr;
    uInt index = 0;

    // just get first todo library
    while(index != libraries.size()) {
        if(!libraries[index]->already_shipping) {
            lib = libraries[index];
            index++;
            break;
        }
        index++;
    }

    uInt metric = 0;
    uInt next_lib = 0;
    for(uInt i = 0; i != libraries.size(); ++i) {
        Library &lib = *libraries[i];

        if(i!=index && !libraries[i]->already_shipping && days_left_till_project_done > lib.M) {

            //metric = (book_score / lib.N )* ( lib.M / lib.T );
            //metric = lib.T * 0.2 + (lib.N / lib.M) * 0.8;
            uInt my_metric = (lib.book_score / lib.N ) * lib.M * ((lib.N/lib.M) / (lib.T + lib.N/lib.M));

            if(my_metric > metric) {
                next_lib = index;
                metric = my_metric;
            }
        }
    }

    return libraries[index];
}

void Algorithm::calculate_book_scores(std::vector<Library *> &libraries, uIntVector &book_scores) {
    /*for (int i = 0; i != libraries.size(); ++i) {
        this->m_threadpool.push([&](int library_idx) {
            Library &lib = *libraries[library_idx];
            metric = lib.N * lib.M / lib.T;

            // Calculate book score
            const auto sum_of_book_scores = std::accumulate(lib.bookIds.begin(), lib.bookIds.end(), 0, [&](auto acc, auto book_idx) {
                return acc + book_scores[book_idx].first;
            });

            lib.book_score = sum_of_book_scores;
        });
    }

    this->m_threadpool.stop(true);*/
}

void Algorithm::run2(uInt D, std::vector<Library *> &libraries, uIntVector& bookScores, uIntVector& librariesToSignUp) {
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


		// Select new library to add;
		//nextLib = getNextLibrary2(librariesTmp, D-day, bookUsed);
		//nextLib = getNextLibrary2(librariesTmp, D-day, bookWillBeUsed);

		if (day < 0) {
			nextLib = getNextLibrary(librariesTmp);
		}
		else {
			nextLib = getNextLibrary2(librariesTmp, D-day, bookWillBeUsed);
		}

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

Library* Algorithm::getNextLibrary(std::vector<Library *>& librariesTmp) {
	Library* libReturn = NULL;

	uInt bestSignUp = 0xFFFFFFF;
	uInt ratePerDay = 0;

	for (uInt i = 0; i < librariesTmp.size(); ++i) {
		Library* lib = librariesTmp[i];
		if (lib->M <= bestSignUp) {
			libReturn = lib;
			bestSignUp = lib->M;
			ratePerDay = lib->T;
		}
	}

	return libReturn;
}


Library* Algorithm::getNextLibrary2(std::vector<Library *>& librariesTmp, uInt daysLeft, std::vector<bool>& bookUsed) {
	Library* libReturn = NULL;

	uInt bestScore = 0;

	for (uInt i = 0; i < librariesTmp.size(); ++i) {
		Library* lib = librariesTmp[i];
		uInt signUpTime = lib->M;

		//std::cout << "M = " << lib->M << " T = " << lib->T << std::endl;

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


Library* Algorithm::getNextLibrary3(std::vector<Library *>& librariesTmp, uInt daysLeft, std::vector<bool>& bookUsed) {
	Library* libReturn = NULL;

	uInt bestScore = 0;

	for (uInt i = 0; i < librariesTmp.size(); ++i) {
		Library* lib = librariesTmp[i];
		uInt signUpTime = lib->M;

		//std::cout << "M = " << lib->M << " T = " << lib->T << std::endl;

		int booksToAdd = daysLeft - signUpTime;

		booksToAdd /= lib->M;

		//std::cout << "booksToAdd = " << booksToAdd << std::endl;
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

			if (score > bestScore) {
				bestScore = score;
				libReturn = lib;
			}
			++index;
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

		//std::cout << "lib: " << lib->id << " bookId " << bookId << " is added" << std::endl;
		++index;
	}
}
