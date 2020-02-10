#include "../lib/Algorithm.h"
#include <iostream>

void Algorithm::run(const uInt numberOfSlices, uIntVector& slicesCount, uIntVector& typesOfPizzaToOrder, uInt& totalNumberOfOrderedSlices) {

	// Number of slices in pizzas is in non-decreasing order.
	typesOfPizzaToOrder.reserve(slicesCount.size());
	std::vector<unsigned int> tmpPizzasToOrder(slicesCount.size());

	unsigned int bestScore = 0;

	for (int i = slicesCount.size() - 1; i >= 0; --i) {
		unsigned int sum = 0;
		tmpPizzasToOrder.clear();
		for (int j = i; j >= 0; --j) {
			if (sum + slicesCount[j] < numberOfSlices) {
				sum += slicesCount[j];
				tmpPizzasToOrder.push_back(j);
				continue;
			}
			if (sum + slicesCount[j] > numberOfSlices) {
				continue;
			}
			if (sum + slicesCount[j] == numberOfSlices) {
				sum += slicesCount[j];
				tmpPizzasToOrder.push_back(j);
				break;
			}
		}
		if (sum > bestScore) {
			bestScore = sum;
			typesOfPizzaToOrder = tmpPizzasToOrder;
		}
		if (sum == numberOfSlices) {
			break;
		}
	}

	totalNumberOfOrderedSlices = bestScore;
	sort(typesOfPizzaToOrder.begin(), typesOfPizzaToOrder.end());
}

void Algorithm::run2(const uInt numberOfSlices, uIntVector& slicesCount, uIntVector& typesOfPizzaToOrder, uInt& totalNumberOfOrderedSlices) {
	typesOfPizzaToOrder.reserve(slicesCount.size());
	uIntVector currentOrder;
	currentOrder.reserve(slicesCount.size());
	uInt currentNumberSlices = 0;

	runRecursion(slicesCount.size() - 1, numberOfSlices, slicesCount, currentOrder, currentNumberSlices, typesOfPizzaToOrder, totalNumberOfOrderedSlices);

	sort(typesOfPizzaToOrder.begin(), typesOfPizzaToOrder.end());
}

void Algorithm::runRecursion(int index, uInt numberOfSlices, uIntVector& slicesCount, uIntVector& currentOrder, uInt& currentNumberSlices, uIntVector& bestOrder, uInt& bestNumberSlices) {
	if (bestNumberSlices == numberOfSlices) {
		return;
	}

	if (index >= 0) {
		uInt slicesCurrentIndex = slicesCount[index];
		uInt totalWithCurrentIndex = slicesCurrentIndex + currentNumberSlices;
		if (totalWithCurrentIndex > numberOfSlices) {
			return runRecursion(index - 1, numberOfSlices, slicesCount, currentOrder, currentNumberSlices, bestOrder, bestNumberSlices);
		}
		else {
			// Further recursion with slices added/not added
			currentOrder.push_back(index);
			currentNumberSlices = totalWithCurrentIndex;
			if (currentNumberSlices > bestNumberSlices) {
				bestOrder = currentOrder;
				bestNumberSlices = currentNumberSlices;
			}

			runRecursion(index - 1, numberOfSlices, slicesCount, currentOrder, currentNumberSlices, bestOrder, bestNumberSlices);

			if (bestNumberSlices == numberOfSlices) {
				return;
			}

			// Again remove slice
			currentOrder.pop_back();
			currentNumberSlices -= slicesCurrentIndex;

			runRecursion(index - 1, numberOfSlices, slicesCount, currentOrder, currentNumberSlices, bestOrder, bestNumberSlices);
		}
	}
}
