#include "io_utils.h"

void RemoveLine(std::istream & in) {
    std::string ignored_chars;
    getline(in, ignored_chars);
}

void ArrayToStream(int size, char ** array, std::stringstream & out) {
    for(int index = 0; index < size; index++) {
        out << array[index];
    }
}

void RemoveWhiteSpaces(std::stringstream & in, std::stringstream & out) {
    char c;
    in >> c;
    while(!in.eof()) {
        out << c;
        in >> c;
    }
}

template<class T>
T ReadNumberInRange(const T min, const T max, std::istream & in) {
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

void SetMaxSignificantDigits(std::ostream & out) {
    out << std::setprecision(15);
}

std::string ReadLine(std::istream & in) {
    std::string line;
    getline(in, line);
    return line;
}

void PrintValue(Token token, std::ostream & out) {
    switch(token.type)
    {
        case TOKEN_DECIMAL: std::cout << token.value.decimalNumber << std::endl; break;
        case TOKEN_OPERATOR: std::cout << token.value.operatorToken << std::endl; break;
        case TOKEN_INTEGER: std::cout << token.value.integerNumber << std::endl; break;
    }
}
