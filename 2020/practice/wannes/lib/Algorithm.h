#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <vector>
#include <string>

class Algorithm {
public:
	Algorithm() {}
    virtual ~Algorithm() {}

    void run(const unsigned int numberOfSlices, std::vector<unsigned int>& slicesCount, std::vector<unsigned int>& typesOfPizzaToOrder, unsigned int& totalNumberOfOrderedSlices);

};

#endif
