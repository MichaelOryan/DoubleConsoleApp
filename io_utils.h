#ifndef IO_UTILS_H
#define IO_UTILS_H

#include <string>
#include <limits>
#include <iostream>
#include <sstream>
#include "calculator.h"
#include <iomanip>

// Prototypes

template<class T>
void PromptValidNumberRange(const T min, const T max, std::ostream & out = std::cout);

void RemoveLine(std::istream & in = std::cin);

template<class T>
T ReadNumberInRange(const T min = std::numeric_limits<T>::min(),
          const T max = std::numeric_limits<T>::max(),
          std::istream & in = std::cin);

void ArrayToStream(int size, char ** array, std::stringstream & out);

void RemoveWhiteSpaces(std::stringstream & in, std::stringstream & out);

// Implementations

template<class T>
T ReadNumberInRange(const T min, const T max, std::istream & in);

template<class T>
void PromptValidNumberRange(const T min, const T max, std::ostream & out);

void SetMaxSignificantDigits(std::ostream & out);

std::string ReadLine(std::istream & in);

void PrintValue(Token token, std::ostream & out);

#endif
