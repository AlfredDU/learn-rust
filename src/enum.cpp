#include <string>
#include <array>
#include <iostream>
#include <cstdlib>

namespace RGBColor {
    typedef std::array<int, 3> RGBTuple;
    
    RGBTuple RED = {255, 0, 0};
    RGBTuple GREEN = {0, 255, 0};
    RGBTuple BLUE = {0, 0, 255};
    RGBTuple BLACK = {0, 0, 0};
    RGBTuple WHITE = {255, 255, 255};
    
    std::string toString(RGBTuple rgb) {
        return "(" + std::to_string(rgb[0]) + ", " + std::to_string(rgb[1]) + ", " +
            std::to_string(rgb[2]) + ")";
    }
}

enum RGB {
    RED = 0,
    GREEN = 1,
    BLUE = 2,
    BLACK = 3,
    WHITE = 4
};

std::string toString(RGB rgb) {
    switch (rgb) {
        case RED:
            return "(255, 0, 0)";
            break;
        case GREEN:
            return "(0, 255, 0)";
            break;
        case BLUE:
            return "(0, 0, 255)";
            break;
        case BLACK:
            return "(0, 0, 0)";
            break;
        case WHITE:
            return "(255, 255, 255)";
            break;
            
        default:
            break;
    }
}


int main(int argc, char* argv[])
{
    std::cout << RGBColor::toString(RGBColor::BLUE) << std::endl;
    
    std::cout << toString(WHITE) << std::endl;
    
    return EXIT_SUCCESS;
}