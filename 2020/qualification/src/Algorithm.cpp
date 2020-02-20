#include "../lib/Algorithm.h"
#include <iostream>
#include <numeric>
#include <thread>
#include <chrono>
using namespace std::chrono_literals;

void Algorithm::run(std::vector<Library *> &libraries, uIntVector &book_scores, uInt D)
{
    library_count = libraries.size();

    // now step through days
    while(today < D && library_count != 0) {
        // select next library that can start sending books
        Library* lib = nullptr;
        if(days_till_signup_done == 0) {
            uIntVector library_results(libraries.size());
            calculate_book_scores(library_results, libraries, book_scores);

            lib = get_next_library(libraries, D - today);
            days_till_signup_done = lib->M;
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

            // calculate book score
            uInt book_score = lib.get_book_score();

            //metric = (book_score / lib.N )* ( lib.M / lib.T );
            //metric = lib.T * 0.2 + (lib.N / lib.M) * 0.8;
            uInt my_metric = (book_score / lib.N ) * lib.M * ((lib.N/lib.M) / (lib.T + lib.N/lib.M));

            if(my_metric > metric) {
                next_lib = index;
            }
        }
    }

    return libraries[index];
}

void Algorithm::calculate_book_scores(uIntVector & library_results, std::vector<Library *> &libraries, uIntVector &book_scores) {
    for (int i = 0; i != libraries.size(); ++i) {
        this->m_threadpool.push([&](int library_idx) {
            Library &lib = *libraries[library_idx];
            metric = lib.N * lib.M / lib.T;

            // Calculate book score
            const auto sum_of_book_scores = std::accumulate(lib.bookIds.begin(), lib.bookIds.end(), 0, [&](auto acc, auto book_idx) {
                return acc + book_scores[book_idx];
            });

            library_results[library_idx] = sum_of_book_scores;
        });
    }

    this->m_threadpool.stop(true);
}

void Algorithm::run2(uInt D, std::vector<Library *> &libraries, uIntVector& bookScores, uIntVector& librariesToSignUp) {
	std::cout << "call run 2" << std::endl;
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
		std::cout << "day " << day << "/" << D << std::endl;
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
				if (nextBookIndex >= lib->bookIds.size()) { // Library finished
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
