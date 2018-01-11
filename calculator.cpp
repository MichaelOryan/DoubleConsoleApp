#include <sstream>
#include <stack>
#include <vector>
#include <queue>
#include <iostream>
#include "io_utils.h"
#include "calculator.h"

namespace calculator
{

Token Add(Token lhs, const Token &rhs);
Token Divide(Token lhs, const Token &rhs);
Decimal Evaluate(std::string &expression);
Token Evaluate(const Token &lhs, const Token &Op, const Token &rhs);
std::vector<Token> ExtractTokens(std::string &expression);
bool IsDecimalPoint(const char &c);
bool IsDecimalPointNext(std::stringstream &in);
bool IsDigit(const char &c);
bool IsGreaterPrecidence(const Token &a, const Token &b);
bool IsNextDigit(std::stringstream &in);
bool IsOperand(const Token &token);
bool IsTokenNumber(const Token &token);
Token MakeDecimalToken(std::stringstream &number, std::stringstream &in);
Token MakeIntegerToken(std::stringstream &number);
Token MakeNumberToken(std::stringstream &in);
Token MakeOperatorToken(std::stringstream &in);
std::queue<Token> MakePostFix(std::vector<Token> tokens);
OperatatorType MapCharToOperatorType(const char &c);
int MapTokenToPrecidence(const Token &a);
void MoveDecimalNumbers(std::stringstream &in, std::stringstream &out);
Token Multiply(Token lhs, const Token &rhs);
Token PostFixEvaluation(std::queue<Token> PostFix);
void PushGreaterPrecidenceToOutput(std::queue<Token> &output, std::stack<Token> &operators, Token token);
void PushOperatorsToOutput(std::stack<Token> &operators, std::queue<Token> &output);
void ReadDigits(std::stringstream &in, std::stringstream &out);
Token ReadToken(std::stringstream &in);
Token Subtract(Token lhs, const Token &rhs);
Token TakeFront(std::queue<Token> & queue);
Token TakeTop(std::stack<Token> & stack);

Decimal Evaluate(std::string &expression)
{
    std::vector<Token> tokens = ExtractTokens(expression);

    std::queue<Token> postFix = MakePostFix(tokens);

    Token result = PostFixEvaluation(postFix);

    return result.value.decimalValue;
}

std::vector<Token> ExtractTokens(std::string &expression)
{
    std::string no_white_spaces = RemoveWhiteSpaces(expression);
    std::stringstream expression_stream(no_white_spaces);

    std::vector<Token> tokens;
    while (!expression_stream.eof())
    {
        Token token = ReadToken(expression_stream);
        tokens.push_back(token);
    }
    return tokens;
}

Token ReadToken(std::stringstream &in)
{
    if (IsNextDigit(in))
    {
        return MakeNumberToken(in);
    }
    else
    {
        return MakeOperatorToken(in);
    }
}

bool IsNextDigit(std::stringstream &in)
{
    return IsDigit(in.peek());
}

bool IsDigit(const char &c)
{
    return c >= '0' && c <= '9';
}

Token MakeNumberToken(std::stringstream &in)
{
    std::stringstream number;

    ReadDigits(in, number);

    if (IsDecimalPointNext(in))
    {
        return MakeDecimalToken(number, in);
    }
    else
    {
        return MakeIntegerToken(number);
    }
}

void ReadDigits(std::stringstream &in, std::stringstream &out)
{
    while (!in.eof() && IsDigit(in.peek()))
    {
        char c;
        in >> c;
        out << c;
    }
}

bool IsDecimalPointNext(std::stringstream &in)
{
    return IsDecimalPoint(in.peek());
}

bool IsDecimalPoint(const char &c)
{
    return c == '.';
}

Token MakeDecimalToken(std::stringstream &number, std::stringstream &in)
{
    Token token;
    token.type = TOKEN_DECIMAL;

    MoveDecimalNumbers(in, number);

    number >> token.value.decimalValue;
    return token;
}

// Naming bad and possibly does too many things
// Maybe ReadFractionDigits
void MoveDecimalNumbers(std::stringstream &in, std::stringstream &out)
{
    // Read in decimal
    char c;
    in >> c;
    out << c;
    ReadDigits(in, out);
}

Token MakeIntegerToken(std::stringstream &number)
{
    Token token;
    token.type = TOKEN_DECIMAL;
    number >> token.value.decimalValue;
    return token;
}


Token MakeOperatorToken(std::stringstream &in)
{
    Token token;
    token.type = TOKEN_OPERATOR;
    char c;
    in >> c;
    token.value.operatorType = MapCharToOperatorType(c);
    return token;
}

OperatatorType MapCharToOperatorType(const char &c)
{
    switch (c)
    {
    case ADDITION_OPERATOR:
        return ADDITION;
    case SUBTRACTION_OPERATOR:
        return SUBTRACTION;
    case MULTIPLICATION_OPERATOR:
        return MULTIPLICATION;
    case DIVISION_OPERATOR:
        return DIVISION;
    default:
        return ADDITION;
    }
}

std::queue<Token> MakePostFix(std::vector<Token> tokens)
{
    std::stack<Token> operators;
    std::queue<Token> output;

    for (Token &token : tokens)
    {
        if (IsTokenNumber(token))
        {
            output.push(token);
        }
        else // Token is operator
        {
            PushGreaterPrecidenceToOutput(output, operators, token);
            operators.push(token);
        }
    }
    PushOperatorsToOutput(operators, output);
    return output;
}

bool IsTokenNumber(const Token &token)
{
    return token.type == TOKEN_DECIMAL;
}

void PushGreaterPrecidenceToOutput(std::queue<Token> &output, std::stack<Token> &operators, Token token)
{
    while (!operators.empty() && IsGreaterPrecidence(operators.top(), token))
    {
        Token token = TakeTop(operators);
        output.push(token);
    }
}

Token TakeTop(std::stack<Token> & stack) {
    Token token;
    token = stack.top();
    stack.pop();
    return token;
}

bool IsGreaterPrecidence(const Token &a, const Token &b)
{
    return MapTokenToPrecidence(a) > MapTokenToPrecidence(b);
}

int MapTokenToPrecidence(const Token &a)
{
    switch (a.value.operatorType)
    {
    case MULTIPLICATION_OPERATOR:
        return MULTIPLICATION_PRECEDENCE;
    case SUBTRACTION_OPERATOR:
        return SUBTRACTION_PRECEDENCE;
    case DIVISION_OPERATOR:
        return DIVISION_PRECEDENCE;
    case ADDITION_OPERATOR:
        return ADDITION_PRECEDENCE;
    }
}

void PushOperatorsToOutput(std::stack<Token> &operators, std::queue<Token> &output)
{
    while (!operators.empty())
    {
        Token token = operators.top();
        operators.pop();
        output.push(token);
    }
}

Token PostFixEvaluation(std::queue<Token> PostFix)
{

    std::stack<Token> operands;
    Token token;

    while (!PostFix.empty())
    {
        token = TakeFront(PostFix);
        if (IsOperand(token))
        {
            operands.push(token);
        }
        else
        { // Evaluate operator with operands, Maybe make a function?
            Token rhs = TakeTop(operands);
            Token lhs = TakeTop(operands);

            Token op = token;

            Token result = Evaluate(lhs, op, rhs);
            operands.push(result);
        }
    }
    Token answer = operands.top();
    return answer;
}

Token TakeFront(std::queue<Token> & queue) {
    Token token;
    token = queue.front();
    queue.pop();
    return token;
}

bool IsOperand(const Token &token)
{
    return token.type == TOKEN_DECIMAL;
}

Token Evaluate(const Token &lhs, const Token &Op, const Token &rhs)
{
    switch (Op.value.operatorType)
    {
    case ADDITION:
        return Add(lhs, rhs);
    case SUBTRACTION:
        return Subtract(lhs, rhs);
    case MULTIPLICATION:
        return Multiply(lhs, rhs);
    case DIVISION:
        return Divide(lhs, rhs);
    default:
        return Add(lhs, rhs);
    }
}

Token Add(Token lhs, const Token &rhs)
{
    lhs.value.decimalValue = lhs.value.decimalValue + rhs.value.decimalValue;
    return lhs;
}

Token Subtract(Token lhs, const Token &rhs)
{
    lhs.value.decimalValue = lhs.value.decimalValue - rhs.value.decimalValue;
    return lhs;
}

Token Multiply(Token lhs, const Token &rhs)
{
    lhs.value.decimalValue = lhs.value.decimalValue * rhs.value.decimalValue;
    return lhs;
}

Token Divide(Token lhs, const Token &rhs)
{
    lhs.value.decimalValue = lhs.value.decimalValue / rhs.value.decimalValue;
    return lhs;
}
}
