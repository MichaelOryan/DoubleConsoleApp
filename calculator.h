#ifndef CALCULATOR_H
#define CALCULATOR_H
#include <sstream>
namespace calculator
{

enum TokenType
{
    TOKEN_DECIMAL,
    TOKEN_OPERATOR
};
enum OperatatorType
{
    CLOSING_BRACE,
    OPENING_BRACE,
    ADDITION,
    SUBTRACTION,
    MULTIPLICATION,
    DIVISION,
    END_OF_EXPRESSION
};

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
    Decimal decimalValue;
    OperatatorType operatorType;
};

struct Token
{
    TokenType type;
    Value value;
};

Decimal Evaluate(std::string &expression);
}
#endif
