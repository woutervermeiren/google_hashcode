#include <iostream>
#include <string>
#include <vector>
#include "../lib/FileHandler.h"
#include "../lib/Algorithm.h"
#include "../lib/Defines.h"
#include <chrono>
using namespace std;

int main()
{
	stringVector fileNames;
	/*fileNames.push_back("a_example");
	fileNames.push_back("b_small");
	fileNames.push_back("c_medium");
	fileNames.push_back("d_quite_big");
	fileNames.push_back("e_also_big");*/


	FileHandler handler;
	Algorithm algorithm;
	std::chrono::steady_clock::time_point begin;
	std::chrono::steady_clock::time_point end;
	std::chrono::steady_clock::time_point beginFull;
	std::chrono::steady_clock::time_point endFull;

	beginFull = std::chrono::steady_clock::now();

	for (stringVector::const_iterator it = fileNames.begin(); it != fileNames.end(); ++it) {
		std::string currentFileName = (*it);

		std::cout << "<<<<< Start file parsing: " << currentFileName << " >>>>>" << std::endl;
		handler.parseInputFile();

		std::cout << "<<<<< Start algorithm execution >>>>>" << std::endl;
		begin = std::chrono::steady_clock::now();

		algorithm.run();

		end = std::chrono::steady_clock::now();
		std::cout << "Algorithm execution took " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " us" << std::endl;

		std::cout << "<<<<< Writing output file  >>>>>" << std::endl;
		begin = std::chrono::steady_clock::now();
		std::string outFileName = currentFileName + ".out";
		handler.writeOutputFile(outFileName);
		end = std::chrono::steady_clock::now();
		std::cout << "Output file creation took " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " us" << std::endl << std::endl;
	}

	endFull = std::chrono::steady_clock::now();

	std::cout << "Full execution took " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " us" << std::endl << std::endl;

    return 0;
}