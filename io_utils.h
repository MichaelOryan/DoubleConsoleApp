#ifndef IO_UTILS_H
#define IO_UTILS_H

#include <string>
#include <limits>
#include <iostream>

// Prototypes

template<class T>
void PromptValidNumberRange(const T min, const T max, std::ostream & out = std::cout);

void RemoveLine(std::istream & in = std::cin);

template<class T>
T ReadIntInRange(const T min = std::numeric_limits<T>::min(),
          const T max = std::numeric_limits<T>::max(),
          std::istream & in = std::cin);


// Implementations

template<class T>
T ReadIntInRange(const T min, const T max, std::istream & in) {
    T number;
    
    in >> number;
    bool read_number_succeeded = in.good();
    
    while (!read_number_succeeded || !IsInRange(number, min, max)) {
        in.clear();
        
        RemoveLine(in);
        
        PromptValidNumberRange(min, max);

        in >> number;
        read_number_succeeded = in.good();
    }
    
    return number;
}

template<class T>
void PromptValidNumberRange(const T min, const T max, std::ostream & out) {
    out << "Please enter a number between ";
    out << min << " and " << max << ": ";
}

#endif