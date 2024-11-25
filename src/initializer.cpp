/*
 * This program needs C++11 support.
 */
#include <map>
#include <vector>
#include <array>
#include <string>
#include <iostream>
#include <cstdlib>

struct avenger {
    std::string aka;
    std::string name;
    std::string actor;
    std::vector<std::string> attends;
    std::map<std::string, std::string> relations;
};


int main(int argc, char* argv[])
{
    std::array<int, 10> fibonacci = {1, 1, 2, 3, 5, 8, 13, 21, 34, 55};
    
    std::cout << "Fibonacci sequence:" << std::endl;
    for (int element : fibonacci) {
        std::cout << element << std::endl;
    }
    
    
    std::vector<int> odds = {1, 3, 5, 7, 9};
    odds.push_back(11);
    std::vector<int> _odds = {13, 15, 17, 19};
    odds.insert(odds.end(), _odds.begin(), _odds.end());
    
    std::cout << "Positive odd sequence:" << std::endl;
    for (int element : odds) {
        std::cout << element << std::endl;
    }
    
    /* Aggregate initialization. */
    avenger captain = {
        "Captain America",
        "Steven Rogers",
        "Chris Evens",
        {
            "Captain America I : the First Avenger",
            "Avengers I",
            "Captain America II : Winter Soldier",
            "Avengers II : Ages of Ultron"
        },
        {
            {"Peggy Carter", "girl friend"}
        }
    };
    
    std::cout << captain.name + ", as known as " + captain.aka + ", is portrayed by "
        + captain.actor + " in the movies of ";
    std::vector<std::string>::size_type checkLast = 0;
    for (std::string element : captain.attends) {
        std::cout << element;
        if (checkLast + 2 < captain.attends.size()) { // Note: std::[generic]::size_type value is always greater or equal to 0, so DO NOT compare a size_type value with (possible) negative values.
            std::cout << ", ";
        } else if (checkLast + 2 == captain.attends.size()) {
            std::cout << " and ";
        }
        checkLast ++;
    }
    std::cout << ", with ";
    checkLast = 0;
    for (auto element : captain.relations) {
        std::cout << element.first + " as " + element.second;
        if (checkLast + 2 < captain.relations.size()) {
            std::cout << ", ";
        } else if (checkLast + 2 == captain.relations.size()) {
            std::cout << " and ";
        }
    }
    std::cout << ".";
    
    return EXIT_SUCCESS;
}