#include <exception>
#include <cmath>
#include <string>
#include <iostream>
#include <cstdlib>


class divided_by_zero : std::exception {
    
public:
    /* Override #what function. */
    const char* what() {
        return "divided by 0";
    };
};

namespace trigonometric {
    
    template <class T> T cot(T __x){
        T tan_value = static_cast<T>(std::tan(__x));
        
        if (tan_value == 0.0) {
            throw divided_by_zero();
        }
        
        return static_cast<T>(1.0) / tan_value;
    };
    
    template <class T> T sec(T __x){
        T cos_value = static_cast<T>(std::cos(__x));
        
        if (cos_value == 0.0) {
            throw divided_by_zero();
        }
        
        return static_cast<T>(1.0) / cos_value;
    };
    
    template <class T> T csc(T __x){
        T sin_value = static_cast<T>(std::sin(__x));
        
        if (sin_value == 0.0) {
            throw divided_by_zero();
        }
        
        return static_cast<T>(1.0) / sin_value;
    };

}

int main(int argc, char* argv[])
{
    float x = 0.0;
    try {
        std::cout << trigonometric::cot(x) << std::endl;
    } catch (divided_by_zero& e) {
        std::cout << e.what() << std::endl;
    }
    
    return EXIT_SUCCESS;
}