#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

#define MAX 100

// Stack structure
struct Stack {
    int top;
    int items[MAX];
};

// Stack functions
void push(struct Stack *stack, int x) {
    if (stack->top == MAX - 1) {
        printf("Stack overflow\n");
        return;
    }
    stack->items[++stack->top] = x;
}

int pop(struct Stack *stack) {
    if (stack->top == -1) {
        printf("Stack underflow\n");
        return -1;
    }
    return stack->items[stack->top--];
}

int peek(struct Stack *stack) {
    return stack->items[stack->top];
}

// Check if a character is an operator
int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}

// Get the precedence of an operator
int precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return 0;
    }
}

// Convert infix expression to postfix
void infixToPostfix(char infix[], char postfix[]) {
    struct Stack opStack;
    opStack.top = -1;
    int i = 0, j = 0;

    while (infix[i] != '\0') {
        // If character is operand, add it to postfix expression
        if (isdigit(infix[i])) {
            postfix[j++] = infix[i];
        }
        // If character is left parenthesis, push it to stack
        else if (infix[i] == '(') {
            push(&opStack, infix[i]);
        }
        // If character is right parenthesis, pop and output from the stack until left parenthesis is found
        else if (infix[i] == ')') {
            while (peek(&opStack) != '(') {
                postfix[j++] = pop(&opStack);
            }
            pop(&opStack); // Remove left parenthesis
        }
        // If an operator is encountered
        else if (isOperator(infix[i])) {
            while (opStack.top != -1 && precedence(peek(&opStack)) >= precedence(infix[i])) {
                postfix[j++] = pop(&opStack);
            }
            push(&opStack, infix[i]);
        }
        i++;
    }

    // Pop all the operators from the stack
    while (opStack.top != -1) {
        postfix[j++] = pop(&opStack);
    }
    postfix[j] = '\0';  // Null-terminate the postfix string
}

// Evaluate a postfix expression
int evaluatePostfix(char postfix[]) {
    struct Stack evalStack;
    evalStack.top = -1;
    int i = 0, a, b, result;

    while (postfix[i] != '\0') {
        if (isdigit(postfix[i])) {
            push(&evalStack, postfix[i] - '0');  // Convert char to int and push onto stack
        } else if (isOperator(postfix[i])) {
            b = pop(&evalStack);
            a = pop(&evalStack);
            switch (postfix[i]) {
                case '+':
                    push(&evalStack, a + b);
                    break;
                case '-':
                    push(&evalStack, a - b);
                    break;
                case '*':
                    push(&evalStack, a * b);
                    break;
                case '/':
                    push(&evalStack, a / b);
                    break;
                case '^':
                    push(&evalStack, pow(a, b));
                    break;
            }
        }
        i++;
    }
    return pop(&evalStack);  // Return the final result
}

int main() {
    char infix[MAX], postfix[MAX];
    int result;

    printf("Enter infix expression: ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);
    printf("Postfix expression: %s\n", postfix);

    result = evaluatePostfix(postfix);
    printf("Result of postfix evaluation: %d\n", result);

    return 0;
}


// OUTPUT:
// Enter infix expression: 1+2-3*8/4-(2+1)*2
// Postfix expression: 12+38*4/-21+2*-
// Result of postfix evaluation: -9
