#include <complex>
#include <cmath>
#include <array>
#include <string>
#include <iostream>
#include <cstdlib>

#define DELTA 0.0001


template <class T> std::string toString(std::complex<T> z) {
    std::stringstream lexical_cast;
    
    lexical_cast << real(z) << " + " << imag(z) << " i";
    std::string result = lexical_cast.str();
    
    return result;
 };

template <class T> std::string toTriString(std::complex<T> z) {
    std::stringstream lexical_cast;
    
    lexical_cast << abs(z) << "(cos[" << arg(z) << "] + i sin[" << arg(z) << "])";
    std::string result = lexical_cast.str();
    
    return result;
};

template <class T, size_t _power> std::array<std::complex<T>, _power> unitRoots(void){
    
    std::array<std::complex<T>, _power> roots;
    T argument = M_PI * 2.0 / static_cast<T>(_power);
    
    for (size_t i = 0; i < _power; i++) {
        roots[i] = std::complex<T>(cos(argument * i), sin(argument * i));
    }
    
    return roots;
};


int main(int argc, char* argv[])
{
    std::complex<double> i(0.0, 1.0); // Standard constructor.
    std::cout << "The unit of imaginary number:" << i << std::endl; // Standard output of complex is like (r, i).
    
    /* Triple root. */
    std::complex<double> phi(- 1.0 / 2, sqrt(3.0) / 2);
    std::cout << toString(phi) << std::endl;
    std::cout <<( abs(pow(phi, 3) - 1.0) < DELTA ? "True" : "False" )<< std::endl; // Note: cannot conduct a arithmetic operator between complex value and int value (must be float or double).
    
    /* Conjugate complex. */
    auto phi_square = conj(phi);
    
    /* Trigonometric format. */
    std::cout << toTriString(phi_square) << std::endl;
    std::cout <<( abs( phi * phi - phi_square ) < DELTA ? "True" : "False" )<< std::endl;
    
    /* Euler equation. */
    std::cout <<( abs(exp( M_PI * i ) + 1.0) < DELTA ? "True" : "False" )<< std::endl;
    
    
    /* Unit roots. */
    auto hexaRoots = unitRoots<double, 6>();
    for (size_t i = 0; i < 6; i++) {
        std::cout << toString(hexaRoots[i]) << std::endl;
        std::cout << (abs( pow(hexaRoots[i], 6) - 1.0 ) < DELTA ? "True" : "False") << std::endl;
    }
    
    return EXIT_SUCCESS;
}