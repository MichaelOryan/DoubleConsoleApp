#ifndef NUMBERS_H
#define NUMBERS_H

#include <stdexcept>
#include <limits>

// Prototypes

template<class T>
T DoubleNumber(const T number);

template<class T>
bool IsDoubleOverflow(const T number);

template<class T>
bool IsDoubleUnderflow(const T number);

template<class T>
T HalveNumber(const T number);

template<class T>
bool IsInRange(const T number, const T min, const T max);


// Implementations

template<class T>
T HalveNumber(const T number) {
    return number / 2;
}

template<class T>
bool IsInRange(const T number, const T min, const T max) {
    return (number >= min) && (number <= max);
}

template<class T>
T DoubleNumber(const T number) {
    
    if (IsDoubleOverflow(number)) {
        throw std::overflow_error("Overflow error!");
    } else if (IsDoubleUnderflow(number)) {
        throw std::underflow_error("Underflow error!");
    }
    
    T double_number = number * 2;
    
    return double_number;
}

template<class T>
bool IsDoubleOverflow(const T number) {
    return number > HalveNumber(std::numeric_limits<T>::max());
}

template<class T>
bool IsDoubleUnderflow(const T number) {
    return number < HalveNumber(std::numeric_limits<T>::min());
}

#endif