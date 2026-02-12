#include "Token.hpp"
using namespace std;

Token::Token() {
    kind = Kind::NUMBER;
    num = 0;
}

Token::Token(const string &strToken) {
    if (strToken.length() == 1) {
        // If it's one character long, it might be one of our arithmetic operators
        if (strToken[0] == '+' || strToken[0] == '-' || strToken[0] == '*' || strToken[0] == '/') {
            kind = Kind::OPERATOR;
            op = strToken[0];
            return;
        }
        // But sometimes it might be a number, like "9"
    }
    // Otherwise, convert it to a double, and pass on the error if we cannot
    kind = Kind::NUMBER;
    try {
        num = stod(strToken);
    } catch (const exception &e) {
        num = 0; // don't leave it uninitialized
        throw string("Error: could not convert \"" + strToken + "\" to Token");
    }
}

Token::Kind Token::getKind() const {
    return kind;
}

double Token::getNumber() const {
    if (kind != Kind::NUMBER) {
        throw string("Cannot getNumber() on token with kind != Token::Kind::NUMBER");
    }
    return num;
}

char Token::getOperator() const {
    if (kind != Kind::OPERATOR) {
        throw string("Cannot getOperator() on token with kind != Token::Kind::OPERATOR");
    }
    return op;
}

ostream& operator<<(ostream &outStream, const Token &myObj) {
    switch (myObj.kind) {
    case Token::Kind::NUMBER:
        outStream << "(Token::Kind::NUMBER, " << myObj.num << ")";
        break;
    case Token::Kind::OPERATOR:
        outStream << "(Token::Kind::OPERATOR, " << myObj.op << ")";
        break;
    }
    return outStream;
}
