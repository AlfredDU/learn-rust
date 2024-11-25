/*
 * This program needs C++11 support.
 */
#include <tuple>
#include <string>
#include <iostream>
#include <cstdlib>


std::tuple<std::string, int, float, std::string, std::string> messi =
    {"Lionel Messi", 28, 1.73, "Argentina", "Forward"};

#define HIGUAIN_TUPLE_SIZE 6
std::tuple<std::string, int, float, std::string, std::string, std::string> higuain =
    {"Gonzalo Higuain", 27, 1.84, "Argentina", "Forward", "Real Mardrid"};


int main(int argc, char* argv[])
{
    std::cout << std::get<0>(messi) << ", aged " << std::get<1>(messi) <<
        ", is a(n) " << std::get<3>(messi) << " player." << std::endl;
    
    /* Dimension of tuple. */
    size_t higuain_tuple_size = std::tuple_size<decltype(higuain)>::value; // Note: the return type is size_t.
    std::cout << higuain_tuple_size << std::endl;
    
    /* Getter and setter of tuple element. */
    std::get<HIGUAIN_TUPLE_SIZE - 1>(higuain) = "Napoli"; // Note: Error occurs when assigning a size_t (or int, long) value to the first parameter (the one enclosed inside angular brackets) of std::get. I do not know why, so a macro alternative is placed there instead.
    std::cout << "The club of Higuain now is " << std::get<HIGUAIN_TUPLE_SIZE - 1>(higuain) << std::endl;
    
    /* Pack. */
    auto aguero = std::make_tuple(std::string{"Kun Aguero"}, 27, 1.76, "Argentina", "Forward", "Manchester City");
    
    /* Unpack */
    std::string aguero_name;
    int aguero_age;
    std::string aguero_nation;
    std::string aguero_position;
    
    std::tie(aguero_name, aguero_age, std::ignore, aguero_nation, aguero_position, std::ignore) = aguero; // Note: use std::ignore to skip elements.
    
    std::cout << aguero_name + ", aged " << aguero_age
        << ", is a(n) " << aguero_nation << " " << aguero_position << "." << std::endl;
    
    return EXIT_SUCCESS;
}