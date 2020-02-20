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

}
