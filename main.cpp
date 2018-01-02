#include <iostream>
#include <stdexcept>
#include "numbers.h"
#include "io_utils.h"

// Function prototypes

template<class T>
void OutputDoubleNumber(const T number, std::ostream & out = std::cout);

void PromptUserForNumber(std::ostream & out = std::cout);

template<class T>
void ReadAndDoubleNumber(std::istream & in = std::cin,
                         std::ostream & out = std::cout);

// Function Implementations

int main() {
    ReadAndDoubleNumber<long long int>(std::cin, std::cout);

    return 0;
}

template<class T>
void ReadAndDoubleNumber(std::istream & in, std::ostream & out) {
    try {
        PromptUserForNumber(out);

        T minimum_number = HalveNumber(std::numeric_limits<T>::min());
        T maximum_number = HalveNumber(std::numeric_limits<T>::max());

        T number = ReadIntInRange(minimum_number, maximum_number, in);
        T double_number = DoubleNumber(number);

        OutputDoubleNumber(double_number, out);
    }
    catch(std::runtime_error e) {
        std::cerr << e.what() << std::endl;
    }
    catch(std::exception e) {
        std::cerr << e.what() << std::endl;
    }
    catch(...) {
        std::cerr << "Unknown Error" << std::endl;
    }

}


void PromptUserForNumber(std::ostream & out) {
    out << "Enter a number to double: ";
}

template<class T>
void OutputDoubleNumber(const T number, std::ostream & out) {
    out << "Double your number is " << number << std::endl;
}
