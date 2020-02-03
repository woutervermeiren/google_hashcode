#include <iostream>
#include <string>
#include <vector>
#include "../lib/FileHandler.h"
#include "../lib/Algorithm.h"
#include <chrono>
using namespace std;

int main()
{

	std::cout << "<<<<< Start file parsing >>>>>" << std::endl;
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

	FileHandler handler;
    std::string fileName = "../d_quite_big.in";
    unsigned int numberOfSlices = 0;
    std::vector<unsigned int> slicesCount;
    bool result = handler.parseInputFile(fileName, numberOfSlices, slicesCount);

    std::cout << "File name: " << fileName << std::endl;
    std::cout << "Number of slices: " << numberOfSlices << std::endl;
    std::cout << "Number of pizzas: " << slicesCount.size() << std::endl;

	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

	std::cout << "File parsing took " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " us" << std::endl;

	std::cout << "<<<<< Start algorithm execution >>>>>" << std::endl;
	begin = std::chrono::steady_clock::now();
	Algorithm algorithm;
    std::vector<unsigned int> pizzasToOrder;
    unsigned int totalNumberOfOrderedSlices;
	algorithm.run(numberOfSlices, slicesCount, pizzasToOrder, totalNumberOfOrderedSlices);
    std::cout << "Going to order " << pizzasToOrder.size() << " pizzas for a total of " << totalNumberOfOrderedSlices << " slices" << std::endl;
	end = std::chrono::steady_clock::now();
	std::cout << "Algorithm execution took " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " us" << std::endl;

	std::cout << "<<<<< Writing output file  >>>>>" << std::endl;
	begin = std::chrono::steady_clock::now();
	handler.writeOutputFile("d_quite_big.out", pizzasToOrder);
	end = std::chrono::steady_clock::now();
	std::cout << "Output file creation took " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " us" << std::endl;

    return result;
}
