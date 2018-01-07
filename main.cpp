#include <iostream>
#include <stdexcept>
#include "io_utils.h"
#include <string>
#include <sstream>
#include "calculator.h"

// Function prototypes

// Function Implementations

int main(int argc, char** argv) {

    SetMaxSignificantDigits(std::cout);

    std::string expression = ReadLine(std::cin);

    std::stringstream with_white_spaces(expression);

    std::stringstream no_white_spaces;

    RemoveWhiteSpaces(with_white_spaces, no_white_spaces);

    Token token = Evaluate(no_white_spaces);

    PrintValue(token, std::cout);

    return 0;
}
