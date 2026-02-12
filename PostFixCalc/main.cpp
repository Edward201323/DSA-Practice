#include "ArrayStack.hpp"
#include "Token.hpp"
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>
using namespace std;

void commandLineCalculator();
double postfixCalculator(const string &postfix_expression);
double postfixCalculator(const Token tokens[], const int SIZE);
void test();

int main() {
    test();
    // commandLineCalculator();
    return 0;
}

// Run an interactive calculator that evaluates each postfix expression the user enters
void commandLineCalculator() {
    string expr;
    double result;
    do {
        cout << "Enter a postfix expression (empty string to quit):" << endl;
        getline(cin, expr);
        if (expr == "") {
            break;
        }
        try {
            result = postfixCalculator(expr);
            cout << "= " << result << endl;
        } catch (const string &e) {
            cout << e << endl;
        }
        cout << endl;
    } while (true);
}

// Test a few hard-coded expressions
void test() {
    string expr;
    double result;

    expr = "3 4 +";
    cout << expr << " = " << postfixCalculator(expr) << " (expected 7)" << endl;

    expr = "8 4 /";
    cout << expr << " = " << postfixCalculator(expr) << " (expected 2)" << endl;

    expr = "5 6 4 - *";
    cout << expr << " = " << postfixCalculator(expr) << " (expected 10)" << endl;

    expr = "1 5 + 3 2 4 / - * 6 +";
    cout << expr << " = " << postfixCalculator(expr) << " (expected 21)" << endl;

    expr = "1 2 3 + + +";
    try {
        result = postfixCalculator(expr);
        cout << expr << " = " << result << " (Uh oh! expected error)" << endl;
    } catch (const string &e) {
        cout << expr << " results in error (good!) " << e << endl;
    }

    expr = "1 2 3 +";
    try {
        result = postfixCalculator(expr);
        cout << expr << " = " << result << " (Uh oh! expected error)" << endl;
    } catch (const string &e) {
        cout << expr << " results in error (good!) " << e << endl;
    }
}

// Given a string represent a postfix expression,
// evaluate it by converting it into an array of Token objects
// and then by calling the overloaded method
double postfixCalculator(const string &postfix_expression) {
    // Separate the given string by whitespaces and turn it into a list (std::vector<string>)
    // For example, "3 4 +" --> ["3", "4", "+"]
    // (Don't worry about understanding how these two lines of code work)
    stringstream ss(postfix_expression);
    vector<string> v{istream_iterator<string>(ss), istream_iterator<string>()};

    // Turn the vector<string> into an array of Token objects
    Token *tokens = new Token[v.size()];
    for (unsigned i = 0; i < v.size(); i++) {
        tokens[i] = Token(v[i]);
    }

    // Call the overloaded method and return it
    double result = postfixCalculator(tokens, v.size());
    delete [] tokens;
    return result;
}

/**
 * Given an array of Token objects, use a stack to evaluate the expression.
 * Example inputs:
 *   tokens = [Token("3"), Token("4"), Token("+")]
 *   SIZE = 3
 * Example output:
 *   7
 * Make sure to throw exceptions if the expression cannot be properly evaluated.
 */

double calculate(double left, double right, char operation){
    if(operation == '+'){
        return left + right;
    }
    else if(operation == '-'){
        return left - right;
    }
    else if(operation == '*'){
        return left * right;
    }
    else if(operation == '/'){
        return left / right;
    } else {
        throw std::string("Invalid operation");
    }
}


double postfixCalculator(const Token tokens[], const int SIZE) {
    if(SIZE % 2 == 0){
        throw std::string("Invalid input");
    }

    ArrayStack<double> nums;
    for(int i = 0; i < SIZE; i++){
        if(tokens[i].getKind() == Token::Kind::NUMBER){
            nums.push(tokens[i].getNumber());
        } else {
            if(nums.getLength() < 2){
                throw std::string("Invalid input");
            }
            double right = nums.peek();
            nums.pop();
            double left = nums.peek();
            nums.pop();
            nums.push(calculate(left, right, tokens[i].getOperator()));
        }
    }

    if(nums.getLength() != 1){
        throw std::string("Invalid input");
    }
    
    return nums.peek();
}
