/*
 * This program needs C++14 support.
 */

#include <cstdlib>
#include <string>
#include <complex>
#include <iostream>


int main(int argc, char* argv[]) {

    /* Unicode string literal */
    std::string english = u8"Hello World!";
    std::string chinese = u8"你好, 世界!";
    std::string greek = u8"γειά σου κόσμος";

    std::cout << english << std::endl;
    // C++ unicode string length cannot be obtained by standard length method
    std::cout << "Count by standard std::string.length() method "  << english.length() << std::endl;
    std::cout << chinese << std::endl;
    std::cout << "Count by standard std::string.length() method "  << chinese.length() << std::endl;
    std::cout << greek << std::endl;
    std::cout << "Count by standard std::string.length() method "  << greek.length() << std::endl;


    /* Complex literal */
    using namespace std::complex_literals;
    std::complex<double> unit_root = - 0.5 + 0.866i;
    auto unit_root_square = pow(unit_root, 2);

    std::cout << "The 3rd unit roots are: 1, " << unit_root << ", " << unit_root_square << std::endl;


    /* E-notation */
    double delta = 1e-4;
    bool negligible = abs(1.0 - unit_root * unit_root_square) <= delta;
    std::cout << std::boolalpha << negligible << std::endl; // use std::boolalpha to output bool as string instead of 1/0

    return EXIT_SUCCESS;
}