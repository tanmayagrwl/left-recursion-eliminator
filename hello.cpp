#include <iostream>
#include <stack>
#include <algorithm>
#include <cctype>
using namespace std;

// Function to check if a character is an operator
bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '%');
}

// Function to get precedence of operators
int getPrecedence(char op) {
    if (op == '^') return 4;
    if (op == '*' || op == '/' || op == '%') return 3;
    if (op == '+' || op == '-') return 2;
    return 0;
}

// Function to reverse a string and swap parentheses
string reverseString(string s) {
    reverse(s.begin(), s.end());
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '(') s[i] = ')';
        else if (s[i] == ')') s[i] = '(';
    }
    return s;
}

// Function to convert infix to postfix notation
string infixToPostfix(string infix) {
    stack<char> st;
    string postfix;
    
    for (char c : infix) {
        if (isalnum(c)) {
            postfix += c;
        }
        else if (c == '(') {
            st.push(c);
        }
        else if (c == ')') {
            while (!st.empty() && st.top() != '(') {
                postfix += st.top();
                st.pop();
            }
            st.pop(); // Remove '(' from stack
        }
        else if (isOperator(c)) {
            while (!st.empty() && getPrecedence(st.top()) >= getPrecedence(c)) {
                postfix += st.top();
                st.pop();
            }
            st.push(c);
        }
    }
    
    while (!st.empty()) {
        postfix += st.top();
        st.pop();
    }
    
    return postfix;
}

// Function to convert infix to prefix notation
string infixToPrefix(string infix) {
    // Step 1: Reverse the infix expression
    string reversedInfix = reverseString(infix);
    
    // Step 2: Convert to postfix (which is reverse of prefix)
    string postfix = infixToPostfix(reversedInfix);
    
    // Step 3: Reverse the postfix to get prefix
    reverse(postfix.begin(), postfix.end());
    
    return postfix;
}

int main() {
    string infix;
    cout << "Enter an infix expression: ";
    getline(cin, infix);
    
    // Remove spaces from the input
    infix.erase(remove(infix.begin(), infix.end(), ' '), infix.end());
    
    string postfix = infixToPostfix(infix);
    string prefix = infixToPrefix(infix);
    
    cout << "Postfix expression: " << postfix << endl;
    cout << "Prefix expression: " << prefix << endl;
    
    return 0;
}