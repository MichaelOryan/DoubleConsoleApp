#include <sstream>
#include <stack>
#include <vector>
#include <queue>
#include "calculator.h"

bool IsDigit(const char & c) {
    return c >= '0' && c <= '9';
}

bool IsDecimalPoint(const char & c) {
    return c == '.';
}

bool IsDecimalPointNext(std::stringstream & in) {
    return IsDecimalPoint(in.peek());
}

char ReadNextNonWhiteSpaceCharacter(std::stringstream & in) {
    char c;
    in >> c;
    return c;
}

void ReadDigits(std::stringstream & in, std::stringstream & out) {

    while(IsDigit(in.peek())) {
        char c;
        in >> c;
        out << c;
    }
}

// Namimg bad and possibly does too many things
void MoveDecimalNumbers(std::stringstream & out, std::stringstream & in) {

    // Read in decimal
    char c;
    in >> c;
    out << c;

    // Read in digits after decimal place
    ReadDigits(in, out);
}

Token MakeDecimalToken(std::stringstream & ss_token, std::stringstream & in) {
    Token token;
    token.type = TOKEN_DECIMAL;

    MoveDecimalNumbers(ss_token, in);

    ss_token >> token.value.decimalNumber;
    return token;
}

Operatator MapCharToOperatorToken(const char & c) {
    switch(c)
    {
        case ADDITION_OPERATOR: return ADDITION; break;
        case SUBTRACTION_OPERATOR: return SUBTRACTION; break;
        case MULTIPLICATION_OPERATOR: return MULTIPLICATION; break;
        case DIVISION_OPERATOR: return DIVISION; break;
        default : return ADDITION;
    }
}

Token MakeOperatorToken(std::stringstream & in) {
    Token token;
    token.type = TOKEN_OPERATOR;
    char c;
    in >> c;
    token.value.operatorToken = MapCharToOperatorToken(c);
    return token;
}

Token MakeIntegerToken(std::stringstream & ss_token) {
    Token token;
    token.type = TOKEN_INTEGER;
    ss_token >> token.value.integerNumber;
    return token;
}

bool IsNextDigit(std::stringstream & in) {
    return IsDigit(in.peek());
}

Token ReadToken(std::stringstream & in) {
    std::stringstream ss_token;

    if(!IsNextDigit(in)) {
      return MakeOperatorToken(in);
    }

    ReadDigits(in, ss_token);

    if(IsDecimalPointNext(in)) {
        return MakeDecimalToken(ss_token, in);
    } else {
        return MakeIntegerToken(ss_token);
    }
}

bool IsTokenNumber(const Token & token) {
    return token.type == TOKEN_INTEGER || token.type == TOKEN_DECIMAL;
}

Token Add(Token lhs, const Token & rhs) {
    lhs.value.integerNumber = lhs.value.integerNumber + rhs.value.integerNumber;
    return lhs;
}

Token Subtract(Token lhs, const Token & rhs) {
    lhs.value.integerNumber = lhs.value.integerNumber - rhs.value.integerNumber;
    return lhs;
}

Token Multiply(Token lhs, const Token & rhs) {
    lhs.value.integerNumber = lhs.value.integerNumber * rhs.value.integerNumber;
    return lhs;
}

Token Divide(Token lhs, const Token & rhs) {
    lhs.value.integerNumber = lhs.value.integerNumber / rhs.value.integerNumber;
    return lhs;
}

bool IsEndOfExpression(const Token & token) {
    return token.type == TOKEN_OPERATOR && token.value.operatorToken == END_OF_EXPRESSION;
}

Token Evaluate (const Token & lhs, const Token & Op, const Token & rhs) {
    switch(Op.value.operatorToken)
    {
        case ADDITION: return Add(lhs, rhs); break;
        case SUBTRACTION: return Subtract(lhs, rhs); break;
        case MULTIPLICATION: return Multiply(lhs, rhs); break;
        case DIVISION: return Divide(lhs, rhs); break;
        default : return Add(lhs, rhs);
    }
}

int MapTokenToPrecidence(const Token & a) {
    switch (a.value.operatorToken)
    {
        case MULTIPLICATION_OPERATOR: return MULTIPLICATION_PRECEDENCE;
        case SUBTRACTION_OPERATOR: return SUBTRACTION_PRECEDENCE;
        case DIVISION_OPERATOR: return DIVISION_PRECEDENCE;
        case ADDITION_OPERATOR: return ADDITION_PRECEDENCE;
    }
}

bool IsGreaterPrecidence(const Token & a, const Token & b) {
    return MapTokenToPrecidence(a) > MapTokenToPrecidence(b);
}

void PushGreaterPrecidenceToOutput(std::queue<Token> & output, std::stack<Token> & operators, Token token) {
    while(!operators.empty() && IsGreaterPrecidence(operators.top(), token)) {
        Token token = operators.top();
        operators.pop();
        output.push(token);
    }
}

std::vector<Token> ExtractTokens(std::stringstream & expression) {
    std::vector<Token> tokens;
    while(!expression.eof()) {
        tokens.push_back(ReadToken(expression));
    }
    return tokens;
}

void PushOperatorsToOutput(std::stack<Token> & operators, std::queue<Token> & output) {
    while(!operators.empty()) {
        Token token = operators.top();
        operators.pop();
        output.push(token);
    }
}

std::queue<Token> MakePostFix(std::vector<Token> tokens) {
  std::stack<Token> operators;
  std::queue<Token> output;

    for(Token & token : tokens) {
        if(IsTokenNumber(token)) {
            output.push(token);
        } else { // Token is operator
            PushGreaterPrecidenceToOutput(output, operators, token);
            operators.push(token);
        }
    }
    PushOperatorsToOutput(operators, output);
    return output;

}

bool IsOperand(const Token & token) {
    bool isOperand = false;
    if(token.type == TOKEN_INTEGER) {
        isOperand = true;
    } else if (token.type == TOKEN_DECIMAL) {
        isOperand = true;
    }
    return isOperand;
}

Token PostFixEvaluation(std::queue<Token> PostFix) {

    std::stack<Token> operands;
    Token token;

    while(!PostFix.empty()) {
        token = PostFix.front();
        PostFix.pop();
        if(IsOperand(token)) {
            operands.push(token);
        } else { // Evaluate operator with operands, Maybe make a function?
            Token rhs = operands.top();
            operands.pop();

            Token lhs = operands.top();
            operands.pop();

            Token op = token;

            Token result = Evaluate(lhs, op, rhs);
            operands.push(result);
        }
    }
    Token answer = operands.top();
    return answer;
}

Token Evaluate (std::stringstream & expression) {
    std::vector<Token> tokens = ExtractTokens(expression);
    std::queue<Token> postFix = MakePostFix(tokens);
    return PostFixEvaluation(postFix);
}
