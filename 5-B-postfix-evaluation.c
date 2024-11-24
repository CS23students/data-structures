#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

// Stack structure
#define MAX 100

typedef struct Stack {
    int top;
    int arr[MAX];
} Stack;

// Initialize stack
void initStack(Stack* s) {
    s->top = -1;
}

// Check if stack is empty
int isEmpty(Stack* s) {
    return s->top == -1;
}

// Check if stack is full
int isFull(Stack* s) {
    return s->top == MAX - 1;
}

// Push element onto stack
void push(Stack* s, int value) {
    if (isFull(s)) {
        printf("Stack overflow.\n");
        exit(EXIT_FAILURE);
    }
    s->arr[++s->top] = value;
}

// Pop element from stack
int pop(Stack* s) {
    if (isEmpty(s)) {
        printf("Stack underflow.\n");
        exit(EXIT_FAILURE);
    }
    return s->arr[s->top--];
}

// Function to evaluate a postfix expression
int evaluatePostfix(const char* expression) {
    Stack stack;
    initStack(&stack);

    for (int i = 0; expression[i] != '\0'; i++) {
        char ch = expression[i];

        // If the character is a space, skip it
        if (isspace(ch)) {
            continue;
        }

        // If the character is a digit, push it onto the stack
        if (isdigit(ch)) {
            int num = 0;

            // Handle multi-digit numbers
            while (isdigit(expression[i])) {
                num = num * 10 + (expression[i] - '0');
                i++;
            }
            i--; // Adjust for the loop increment
            push(&stack, num);
        } 
        // If the character is an operator, pop two elements and apply the operator
        else {
            int val2 = pop(&stack);
            int val1 = pop(&stack);

            switch (ch) {
                case '+':
                    push(&stack, val1 + val2);
                    break;
                case '-':
                    push(&stack, val1 - val2);
                    break;
                case '*':
                    push(&stack, val1 * val2);
                    break;
                case '/':
                    if (val2 == 0) {
                        printf("Division by zero error.\n");
                        exit(EXIT_FAILURE);
                    }
                    push(&stack, val1 / val2);
                    break;
                case '^':
                    push(&stack, pow(val1, val2));
                    break;
                default:
                    printf("Invalid operator '%c'.\n", ch);
                    exit(EXIT_FAILURE);
            }
        }
    }

    // The final result is the only element left in the stack
    return pop(&stack);
}

// Driver function
int main() {
    char expression[MAX];

    printf("Enter a postfix expression: ");
    fgets(expression, MAX, stdin);

    int result = evaluatePostfix(expression);
    printf("Result of the postfix expression: %d\n", result);

    return 0;
}



// SAMPLE OUTPUT 1:
// Enter a postfix expression: 10 20 + 3 *
// Result of the postfix expression: 90

// SAMPLE OUTPUT 2:
// Enter a postfix expression: 5 3 4 + *
// Result of the postfix expression: 35
