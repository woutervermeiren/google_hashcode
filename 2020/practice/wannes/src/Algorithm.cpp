#include "../lib/Algorithm.h"

void Algorithm::run(const unsigned int numberOfSlices, std::vector<unsigned int>& slicesCount, std::vector<unsigned int>& typesOfPizzaToOrder, unsigned int& totalNumberOfOrderedSlices) {

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
