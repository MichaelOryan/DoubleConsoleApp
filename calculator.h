#ifndef CALCULATOR_H
#define CALCULATOR_H
#include <sstream>

enum TokenType { TOKEN_INTEGER, TOKEN_DECIMAL, TOKEN_OPERATOR };
enum Operatator { CLOSING_BRACE, OPENING_BRACE, ADDITION, SUBTRACTION, MULTIPLICATION, DIVISION, END_OF_EXPRESSION };

const char DIVISION_OPERATOR = '/';
const char MULTIPLICATION_OPERATOR = '*';
const char ADDITION_OPERATOR = '+';
const char SUBTRACTION_OPERATOR = '-';

const unsigned int MULTIPLICATION_PRECEDENCE = 20;
const unsigned int DIVISION_PRECEDENCE = 20;

const unsigned int SUBTRACTION_PRECEDENCE = 10;
const unsigned int ADDITION_PRECEDENCE = 10;


typedef long long int Integer;
typedef long double Decimal;

union Value {
    Integer integerNumber;
    Decimal decimalNumber;
    Operatator operatorToken;
};

struct Token {
    TokenType type;
    Value value;
};


Token Evaluate (std::stringstream & expression);

#endif
