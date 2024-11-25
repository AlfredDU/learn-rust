/*
 * This program needs C++11 support.
 */
#include <iostream>
#include <cstdlib>


/* Finite field based on certain prime number. */
template <int _zero> struct finiteField_element {
    int value;
};

template <int _zero>
    finiteField_element<_zero> operator+ (finiteField_element<_zero> x1, finiteField_element<_zero> x2)
{
    return finiteField_element<_zero>{ (x1.value + x2.value) % _zero };
};

template <int _zero>
    finiteField_element<_zero> operator- (finiteField_element<_zero> x1, finiteField_element<_zero> x2)
{
    return finiteField_element<_zero>{ (x1.value - x2.value) % _zero };
};

template <int _zero>
    finiteField_element<_zero> operator* (finiteField_element<_zero> x1, finiteField_element<_zero> x2)
{
    return finiteField_element<_zero>{ (x1.value * x2.value) % _zero };
};

template <int _zero>
    finiteField_element<_zero> operator/ (finiteField_element<_zero> x1, finiteField_element<_zero> x2)
{
    for (int i = 0; i < _zero; i++) {
        if ((i * x2.value) % _zero == x1.value % _zero ) {
            return finiteField_element<_zero>{i};
        }
    }
    
    return finiteField_element<_zero>{0};
};

template <int _zero> bool operator== (const finiteField_element<_zero>& x1, const finiteField_element<_zero>& x2) {
    if ( (x1.value - x2.value) % _zero == 0 ) {
        return true;
    } else {
        return false;
    }
};


int main(int argc, char* argv[])
{
    finiteField_element<5> Five_0, Five_1, Five_2, Five_3, Five_4;
    Five_0 = {0};
    Five_1 = {1};
    Five_2 = {2};
    Five_3 = {3};
    Five_4 = {4};
    
    std::cout << (Five_3 / Five_4 == Five_2) << std::endl;
    
    return EXIT_SUCCESS;
}