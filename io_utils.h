#ifndef IO_UTILS_H
#define IO_UTILS_H

#include <string>
#include <sstream>

std::string ReadLine(std::istream &in);
std::string RemoveWhiteSpaces(std::string in);
void SetMaxSignificantDigits(std::ostream &out);

#endif
