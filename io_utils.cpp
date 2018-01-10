#include "io_utils.h"
#include <iomanip>
#include <sstream>
#include <string>

void RemoveWhiteSpaces(std::stringstream &in, std::stringstream &out);

void RemoveWhiteSpaces(std::stringstream &in, std::stringstream &out)
{
    char c;
    in >> c;
    while (!in.eof())
    {
        out << c;
        in >> c;
    }
}

std::string RemoveWhiteSpaces(std::string in)
{
    std::stringstream with_white_spaces(in);
    std::stringstream no_white_spaces;
    RemoveWhiteSpaces(with_white_spaces, no_white_spaces);
    return no_white_spaces.str();
}

void SetMaxSignificantDigits(std::ostream &out)
{
    out << std::setprecision(15);
}

std::string ReadLine(std::istream &in)
{
    std::string line;
    getline(in, line);
    return line;
}
