#include "myalgo.h"

#include <algorithm>
#include <iostream>

void myalgo::simple_order(myint M, vector<myint> &slices, vector<myint> &orders)
{
    // just sort max to min
    sort(slices.begin(), slices.end(), greater<myint>());

    myint index = 0;
    myint slice_count = 0;
    bool max_reached = false;
    while (index < slices.size() && !max_reached) {
        //cerr << "slice " << index << ": " << slices[index] << endl;
        if (slice_count + slices[index] <= M) {
            orders.push_back(index);
            slice_count += slices[index];
        }
        if (slice_count == M) {
            max_reached = true;
        }
        ++index;
    }
}
