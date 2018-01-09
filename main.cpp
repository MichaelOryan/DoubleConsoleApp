#include <iostream>
#include "io_utils.h"
#include <string>
#include <sstream>
#include "calculator.h"

// Function prototypes

// Function Implementations

int main(int argc, char** argv) {

    SetMaxSignificantDigits(std::cout);

    std::string expression = ReadLine(std::cin);

    calculator::Decimal result = calculator::Evaluate(expression);

    std::cout << result << std::endl;;

    return 0;
}
