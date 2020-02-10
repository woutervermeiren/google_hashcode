#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <vector>
#include <string>
#include "Defines.h"

class Algorithm {
public:
	Algorithm() {}
    virtual ~Algorithm() {}

    void run(const uInt numberOfSlices, uIntVector& slicesCount, uIntVector& typesOfPizzaToOrder, uInt& totalNumberOfOrderedSlices);

    void run2(const uInt numberOfSlices, uIntVector& slicesCount, uIntVector& typesOfPizzaToOrder, uInt& totalNumberOfOrderedSlices);

protected:
    void runRecursion(int index, uInt numberOfSlices, uIntVector& slicesCount, uIntVector& currentOrder, uInt& currentNumberSlices, uIntVector& bestOrder, uInt& bestNumberSlices);
};

#endif
