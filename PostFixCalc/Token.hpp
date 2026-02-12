#pragma once

#include <ostream>
#include <string>

class Token {
public:
    enum class Kind {
        OPERATOR,
        NUMBER
    };

private:
    Kind kind;
    double num;
    char op;

public:
    Token();
    Token(const std::string &strToken);

    // Returns either Token::Kind::OPERATOR or Token::Kind::NUMBER,
    // which tells you whether this contains an operator or a number, respectively
    Kind getKind() const;

    // Returns the number this token represents
    // (but throws an exception if kind != Token::Kind::NUMBER)
    double getNumber() const;

    // Returns the operator this token represents:
    // either '+', '-', '*', or '/'
    // (but throws an exception if kind != Token::Kind::OPERATOR)
    char getOperator() const;

    // Provided so that you can `cout` your Token objects.
    friend std::ostream& operator<<(std::ostream&, const Token&);
};
