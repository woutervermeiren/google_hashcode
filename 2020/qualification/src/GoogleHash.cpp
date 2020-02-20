#include "../lib/Algorithm.h"
#include "../lib/Defines.h"
#include "../lib/FileHandler.h"
#include <chrono>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
    stringVector fileNames;
    fileNames.push_back("a_example.txt");
    fileNames.push_back("b_read_on.txt");
    fileNames.push_back("c_incunabula.txt");
    fileNames.push_back("d_tough_choices.txt");
    fileNames.push_back("f_libraries_of_the_world.txt");

    FileHandler handler;
    Algorithm algorithm;
    std::chrono::steady_clock::time_point begin;
    std::chrono::steady_clock::time_point end;
    std::chrono::steady_clock::time_point beginFull;
    std::chrono::steady_clock::time_point endFull;

    beginFull = std::chrono::steady_clock::now();

    for (stringVector::const_iterator it = fileNames.begin(); it != fileNames.end(); ++it) {
        std::string currentFileName = (*it);

        uInt B;
        uInt L;
        uInt D;

        uIntVector bookScores;

        std::vector<Library *> libraries;

        std::cout << "<<<<< Start file parsing: " << currentFileName << " >>>>>" << std::endl;
        handler.parseInputFile(currentFileName, B, L, D, bookScores, libraries);

        std::cout << "<<<<< Start algorithm execution >>>>>" << std::endl;
        begin = std::chrono::steady_clock::now();

        algorithm.run(libraries);

        end = std::chrono::steady_clock::now();
        std::cout << "Algorithm execution took "
                  << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " us" << std::endl;

        std::cout << "<<<<< Writing output file  >>>>>" << std::endl;
        begin = std::chrono::steady_clock::now();
        std::string outFileName = currentFileName + ".out";
        handler.writeOutputFile(outFileName);
        end = std::chrono::steady_clock::now();
        std::cout << "Output file creation took "
                  << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " us" << std::endl
                  << std::endl;

        for (uInt i = 0; i < libraries.size(); ++i) {
            delete libraries[i];
        }
    }

    endFull = std::chrono::steady_clock::now();

    std::cout << "Full execution took " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()
              << " us" << std::endl
              << std::endl;

    return 0;
}
