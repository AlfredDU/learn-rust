#include <iostream>
#include <cstdlib>


long factorial(unsigned int n) {
    if (n == 0 || n == 1) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
};

long factorial_revised(unsigned int n) {
    
    long result = 1;
    
    for (unsigned int i = 1; i <= n ; i++) {
        result *= i;
    }
    
    return result;
};


long fibonacci(unsigned int n) {
    if (n == 0 || n == 1) {
        return 1;
    } else {
        return fibonacci(n - 1) + fibonacci(n - 2);
    }
}; // When n up to 50 than the recursion seems to get stuck.

long fibonacci_revised(unsigned int n) {
  
    long swap[2];
    swap[0] = 1;
    swap[1] = 1;
    
    if (n == 0) {
        return swap[0];
    }
    
    if (n == 1) {
        return swap[1];
    }
    
    for (unsigned int i = 2; i <= n; i++) {
        
        long third = swap[0] + swap[1];
        swap[0] = swap[1];
        swap[1] = third;
    }
    
    return swap[1];
};


int main(int argc, char* argv[])
{
    std::cout << fibonacci_revised(100) << std::endl;
    std::cout << fibonacci(100) << std::endl;
    
    std::cout << "end" << std::endl;
    
    return EXIT_SUCCESS;
}