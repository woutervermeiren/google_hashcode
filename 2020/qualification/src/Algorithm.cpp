#include "../lib/Algorithm.h"
#include <iostream>
#include <numeric>
#include <thread>
#include <chrono>
using namespace std::chrono_literals;

void Algorithm::run(std::vector<Library *> &libraries, uIntVector &book_scores)
{
    uIntVector library_results(libraries.size());

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

    while (this->m_threadpool.n_idle() != 0) {

        std::this_thread::sleep_for(1s);
    }

    library_count = libraries.size();

    while(today < D && library_count != 0) {
        if(days_till_signup_done == 0) {
            Library* lib = get_next_library(libraries);
            days_till_signup_done = lib->M;
        }

        days_till_signup_done--;
    }
}

Library* Algorithm::get_next_library(std::vector<Library *> &libraries) {
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
        if(i!=index && !libraries[i]->already_shipping) {
            Library &lib = *libraries[i];

            // calculate book score
            uInt book_score = lib.get_book_score();

            //metric = (book_score / lib.N )* ( lib.M / lib.T );
            //metric = lib.T * 0.2 + (lib.N / lib.M) * 0.8;
            uInt my_metric = (book_score / lib.N ) * lib.M * ( (lib.T + lib.N/lib.M))/(lib.N/lib.M);

            if(my_metric > metric) {
                next_lib = index;
            }
        }
    }

    return libraries[index];
}
