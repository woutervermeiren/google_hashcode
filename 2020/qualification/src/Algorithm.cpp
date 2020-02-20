#include "../lib/Algorithm.h"
#include <iostream>

void Algorithm::run(std::vector<Library *> &libraries)
{
    for (int i = 0; i != libraries.size(); ++i) {
        Library &lib = *libraries[i];
        metric = lib.N * lib.M / lib.T;
    }
}
