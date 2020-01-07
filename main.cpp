#include <iostream>
#include <fstream>

#include "TrieMap.hpp"

#define nl '\n'

int main(int argc, char **argv){
    std::ifstream natReader(argv[1]);
    std::ifstream flowReader(argv[2]);

    if (!(natReader.is_open() && flowReader.is_open())) {
        std::cout << "Error with file arguments" << nl;
        return -1;
    }

    std::ofstream outputWriter("OUTPUT");
    if (!outputWriter.is_open()) {
        std::cout << "Error writing to OUTPUT" << nl;
        return -1;
    }

    TrieMap *tm = new TrieMap;

    std::string firstStr;
    while(std::getline(natReader, firstStr, ',')) {
        std::string secondStr;
        std::getline(natReader, secondStr);
        tm->insertNAT(firstStr, secondStr);
    }

    std::string flowStr;
    while(std::getline(flowReader, flowStr)) {
        std::string result = tm->retrieveNAT(flowStr);
        if (result.empty()) {
            outputWriter << "No nat match for " << flowStr << nl;
        } else {
            outputWriter << flowStr << " -> " << result << nl;
        }
    }

    natReader.close();
    flowReader.close();
    outputWriter.close();

    return 0;
}
