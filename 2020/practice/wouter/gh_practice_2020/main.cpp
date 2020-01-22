#include <iostream>
#include <limits>
#include <numeric>
#include <string>
#include <vector>

#include "myalgo.h"

using namespace std;

int main()
{
    myalgo algo;
    // inputs
    myint M = numeric_limits<myint>::max();
    myint N = numeric_limits<myint>::max();
    vector<myint> slices;

    // outputs
    vector<myint> orders;

    // parse input
    string input;
    myint input_index = 0;
    while (cin >> input) {
        if (input_index == 0) {
            M = stoul(input);
        } else if (input_index == 1) {
            N = stoul(input);
            slices.reserve(N);
        } else {
            slices.push_back(stoul(input));
        }
        ++input_index;
    }

    /// ALGO START
    cerr << "Starting algo >>>>>>>>>>>" << endl;
    algo.simple_order(M, slices, orders);
    cerr << "<<<<<<<<<< Finished algo" << endl;
    /// ALGO STOP

    // some nice output with error checking
    cerr << "max number of pizza slices: " << M << endl;
    cerr << "number of pizza types: " << N << endl;
    cerr << "number of orders: " << orders.size();
    if (orders.size() > M) {
        cerr << "  <----- ERROR" << endl;
    } else {
        cerr << endl;
    }
    cerr << "order size: " << orders.size() << endl;
    myint total_slices = static_cast<myint>(accumulate(orders.begin(), orders.end(), 0));
    cerr << "total slices: " << total_slices;
    if (total_slices == 0 || total_slices > M) {
        cerr << "  <----- ERROR" << endl;
    } else {
        cerr << endl;
    }
    cerr << "Selected pizza's:" << endl;
    for (myint i = 0; i != orders.size(); ++i) {
        cerr << "(" << i << "," << slices[orders[i]] << ")";
        if (i != orders.size() - 1) {
            cerr << "-";
        }
    }
    cerr << endl;
    cerr << "SCORE: ";
    myint score = 0;
    for (myint i = 0; i != orders.size(); ++i) {
        myint slice_index = orders[i];
        score += slices[slice_index];
    }
    cerr << score << endl;

    // write output
    cout << orders.size() << endl;
    myint i = 0;
    while (i != orders.size()) {
        cout << i;
        i++;
        if (i != orders.size()) {
            cout << " ";
        } else {
            cout << endl;
        }
    }

    return 0;
}
