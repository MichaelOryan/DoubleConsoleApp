#include <sstream>
#include <stack>
#include <vector>
#include <queue>
#include "calculator.h"
#include <iostream>
#include "io_utils.h"

namespace calculator {

    Token Add(Token lhs, const Token & rhs);
    Token Divide(Token lhs, const Token & rhs);
    Decimal Evaluate (std::string & expression);
    Token Evaluate (const Token & lhs, const Token & Op, const Token & rhs);
    std::vector<Token> ExtractTokens(std::string & expression);
    bool IsDecimalPoint(const char & c);
    bool IsDecimalPointNext(std::stringstream & in);
    bool IsDigit(const char & c);
    bool IsGreaterPrecidence(const Token & a, const Token & b);
    bool IsNextDigit(std::stringstream & in);
    bool IsOperand(const Token & token);
    bool IsTokenNumber(const Token & token);
    Token MakeDecimalToken(std::stringstream & ss_token, std::stringstream & in);
    Token MakeIntegerToken(std::stringstream & ss_token);
    Token MakeOperatorToken(std::stringstream & in);
    std::queue<Token> MakePostFix(std::vector<Token> tokens);
    Operatator MapCharToOperatorToken(const char & c);
    int MapTokenToPrecidence(const Token & a);
    void MoveDecimalNumbers(std::stringstream & in, std::stringstream & out);
    Token Multiply(Token lhs, const Token & rhs);
    Token PostFixEvaluation(std::queue<Token> PostFix);
    void PushGreaterPrecidenceToOutput(std::queue<Token> & output, std::stack<Token> & operators, Token token);
    void PushOperatorsToOutput(std::stack<Token> & operators, std::queue<Token> & output);
    void ReadDigits(std::stringstream & in, std::stringstream & out);
    Token ReadToken(std::stringstream & in);
    Token Subtract(Token lhs, const Token & rhs);

    Decimal Evaluate (std::string & expression) {

        std::vector<Token> tokens = ExtractTokens(expression);

        std::queue<Token> postFix = MakePostFix(tokens);

        Token result = PostFixEvaluation(postFix);
        return result.value.decimalNumber;
    }

    std::vector<Token> ExtractTokens(std::string & expression) {
        std::string no_white_spaces = RemoveWhiteSpaces(expression);
        std::stringstream expression_stream(no_white_spaces);

        std::vector<Token> tokens;
        while(!expression_stream.eof()) {
            tokens.push_back(ReadToken(expression_stream));
        }
        return tokens;
    }

    Token ReadToken(std::stringstream & in) {

        std::stringstream ss_token;

        if(!IsNextDigit(in)) {
          return MakeOperatorToken(in);
        }

        ReadDigits(in, ss_token);

        if(IsDecimalPointNext(in)) {
            //std::cout << "Read Decimal" << std::endl;
            return MakeDecimalToken(ss_token, in);
        } else {
            return MakeIntegerToken(ss_token);
        }
    }

    bool IsNextDigit(std::stringstream & in) {
        return IsDigit(in.peek());
    }

    bool IsDigit(const char & c) {
        return c >= '0' && c <= '9';
    }

    Token MakeOperatorToken(std::stringstream & in) {
        Token token;
        token.type = TOKEN_OPERATOR;
        char c;
        in >> c;
        token.value.operatorToken = MapCharToOperatorToken(c);
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

    void ReadDigits(std::stringstream & in, std::stringstream & out) {

        while(!in.eof() && IsDigit(in.peek())) {
            char c;
            in >> c;
            out << c;
        }
    }

    bool IsDecimalPointNext(std::stringstream & in) {
        return IsDecimalPoint(in.peek());
    }

    bool IsDecimalPoint(const char & c) {
        return c == '.';
    }

    Token MakeDecimalToken(std::stringstream & ss_token, std::stringstream & in) {
        Token token;
        token.type = TOKEN_DECIMAL;
        //std::cout << "Read Decimal Token" << std::endl;
        MoveDecimalNumbers(in, ss_token);

        ss_token >> token.value.decimalNumber;
        return token;
    }

    // Namimg bad and possibly does too many things
    void MoveDecimalNumbers(std::stringstream & in, std::stringstream & out) {
        // Read in decimal
        char c;
        in >> c;
        out << c;
        //std::cout << out.str() << std::endl;
        // Read in digits after decimal place
        ReadDigits(in, out);
    }

    Token MakeIntegerToken(std::stringstream & ss_token) {
        Token token;
        token.type = TOKEN_DECIMAL;
        ss_token >> token.value.decimalNumber;
        return token;
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

    bool IsTokenNumber(const Token & token) {
        return token.type == TOKEN_DECIMAL;
    }

    void PushGreaterPrecidenceToOutput(std::queue<Token> & output, std::stack<Token> & operators, Token token) {
        while(!operators.empty() && IsGreaterPrecidence(operators.top(), token)) {
            Token token = operators.top();
            operators.pop();
            output.push(token);
        }
    }

    bool IsGreaterPrecidence(const Token & a, const Token & b) {
        return MapTokenToPrecidence(a) > MapTokenToPrecidence(b);
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

    void PushOperatorsToOutput(std::stack<Token> & operators, std::queue<Token> & output) {
        while(!operators.empty()) {
            Token token = operators.top();
            operators.pop();
            output.push(token);
        }
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

    bool IsOperand(const Token & token) {
        return token.type == TOKEN_DECIMAL;
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

    Token Add(Token lhs, const Token & rhs) {
        lhs.value.decimalNumber = lhs.value.decimalNumber + rhs.value.decimalNumber;
        return lhs;
    }

    Token Subtract(Token lhs, const Token & rhs) {
        lhs.value.decimalNumber = lhs.value.decimalNumber - rhs.value.decimalNumber;
        return lhs;
    }

    Token Multiply(Token lhs, const Token & rhs) {
        lhs.value.decimalNumber = lhs.value.decimalNumber * rhs.value.decimalNumber;
        return lhs;
    }

    Token Divide(Token lhs, const Token & rhs) {
        lhs.value.decimalNumber = lhs.value.decimalNumber / rhs.value.decimalNumber;
        return lhs;
    }

}
