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

    //std::cout << "selecting next library" << std::endl;

    // just get first todo library
    while(index != libraries.size()) {
        if(!libraries[index]->already_shipping) {
            lib = libraries[index];
            break;
        }
        index++;
    }

    //std::cout << "first todo: " << index << std::endl;
    float metric = 0;

    for(uInt i = 0; i != libraries.size(); ++i) {
        Library &lib = *libraries[i];

        if(i!=index && !libraries[i]->already_shipping && days_left_till_project_done > lib.M) {

            //metric = (book_score / lib.N )* ( lib.M / lib.T );
            //metric = lib.T * 0.2 + (lib.N / lib.M) * 0.8;
            //std::cout << "score: " << lib.book_score << std::endl;
            //float my_metric = (1.0*lib.book_score / lib.N ) * lib.M * (1.0 * (lib.N/lib.M) / (lib.T + lib.N*1.0/lib.M));
            float my_metric = ( days_left_till_project_done - lib.T )*1.0 * ( 1.0*(lib.book_score * lib.M ) / lib.N);
            //std::cout << "lib " << lib.id << " my_metric: " << my_metric << std::endl;

            //std::cout << "metric - my_metric : " << metric << " - " << my_metric << std::endl;
            if(my_metric > metric) {
                metric = my_metric;
                index = i;
            }
        }
    }
    //std::cout << "library selected: " << index << libraries[index]->book_score <<  std::endl;;

    return libraries[index];
}

void Algorithm::calculate_book_scores(std::vector<Library *> &libraries, uIntVector &book_scores) {
    //std::cout << "book scores " << libraries.size() << " " << book_scores.size() << std::endl;
    for (int i = 0; i != libraries.size(); ++i) {
        //this->m_threadpool.push([&](int library_idx) {
            Library &lib = *libraries[i];
            metric = lib.N * lib.M / lib.T;

            // Calculate book score
            const auto sum_of_book_scores = std::accumulate(lib.bookIds.begin(), lib.bookIds.end(), 0, [&](auto acc, auto book_idx) {
                return acc + book_scores[book_idx];
            });

            lib.book_score = sum_of_book_scores;
            //std::cout << "lib: " << lib.id << " : " << lib.book_score << std::endl;
        //});
    }

    //this->m_threadpool.stop(true);
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
		if (signupTime == 0) {
            calculate_book_scores(libraries, bookScores);
			if (nextLib != NULL) {
				librariesToSignUp.push_back(nextLib->id);
                std::cout << "day " << day << "/" << D << " -> lib " << nextLib->id << std::endl;
                nextLib->already_shipping = true;
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
        //nextLib = getNextLibrary(librariesTmp);
        nextLib = get_next_library(libraries, D - day);
        librariesTmp = libraries;
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
