#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char stack[30]; // Stack for parsing
int top = -1;   // Stack pointer

void push(char c) {
    stack[++top] = c;
}

char pop() {
    if (top >= 0)
        return stack[top--];
    return 'x'; // Error handling if stack is empty
}

void printStack() {
    printf("\n\t\t\t $");
    for (int i = 0; i <= top; i++)
        printf("%c", stack[i]);
}

int main() {
    char input[20];
    int i, length;
    
    printf("\n\n\t\t LR(0) PARSER");
    printf("\n\t\t ENTER THE EXPRESSION: ");
    scanf("%s", input);
    
    length = strlen(input);
    
    printf("\n\t\t $");
    
    // **Step 1: Shift and push tokens**
    for (i = 0; i < length; i++) {
        // Handle 'id' (identifier) as E
        if (i < length - 1 && input[i] == 'i' && input[i + 1] == 'd') {
            printStack();
            printf(" id");
            push('E'); // Reduce 'id' to 'E'
            printStack();
            i++; // Skip 'd' in 'id'
        } 
        // Handle operators (+, -, *, /)
        else if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/') {
            push(input[i]);
            printStack();
        }
        // Invalid character
        else {
            printf("\n\t\t ERROR: Unexpected character '%c'", input[i]);
            return 1;
        }
    }
    
    printStack();
    
    // **Step 2: Reduce E op E -> E**
    while (top >= 2) {
        char right = pop(); // First element (should be 'E')
        char op = pop();    // Operator (+, -, *, /)
        char left = pop();  // Second element (should be 'E')

        if (right == 'E' && left == 'E' && (op == '+' || op == '-' || op == '*' || op == '/')) {
            push('E'); // Reduce to E
            printStack();
            printf(" (Reduce: E %c E -> E)", op);
        } else {
            printf("\n\t\t ERROR: Invalid reduction at '%c %c %c'", left, op, right);
            return 1;
        }
    }
    
    // **Final Check: Parsing Successful**
    if (top == 0 && stack[top] == 'E') {
        printf("\n\n\t\t PARSING SUCCESSFUL!");
    } else {
        printf("\n\n\t\t PARSING FAILED!");
    }
    
    printf("\n\n\t\t Press Enter to exit...");
    getchar(); // Clear input buffer
    getchar(); // Wait for user input
    
    return 0;
}
