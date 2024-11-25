/*
 * This program needs C++11 support.
 */
#include <string>
#include <cmath>
#include <array>
#include <iostream>
#include <cstdlib>


typedef std::array<float, 2> Vector2f;
typedef std::array<std::array<float, 2>, 2> Matrix2x2f;
Vector2f rotate(Vector2f vec, float angle);
std::string toString(Vector2f vec);


int main(int argc, char* argv[]){
    
    Vector2f xUnit = {1.0, 0.0};
    Vector2f unit = rotate(xUnit, M_PI / 6.0);
    
    std::cout << toString(unit) << std::endl;
    
    return EXIT_SUCCESS;
}


Vector2f rotate(Vector2f vec, float angle){
    
    Matrix2x2f rotateMatrix = {{
        { static_cast<float>(cos(angle)), static_cast<float>(- sin(angle)) },
        { static_cast<float>(sin(angle)), static_cast<float>(cos(angle)) }
    }}; // Note: the outer double brackets is necessary. 
    
    Vector2f result = {
        rotateMatrix[0][0] * vec[0] + rotateMatrix[0][1] * vec[1],
        rotateMatrix[1][0] * vec[0] + rotateMatrix[1][1] * vec[1]
    };
    return result;
}

std::string toString(Vector2f vec){
    return "(" + std::to_string(vec[0]) + ", " + std::to_string(vec[1]) + ")";
}

